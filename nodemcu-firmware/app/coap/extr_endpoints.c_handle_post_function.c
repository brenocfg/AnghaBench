#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  coap_rw_buffer_t ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  p; } ;
struct TYPE_19__ {int /*<<< orphan*/  tok; TYPE_4__ payload; } ;
typedef  TYPE_5__ coap_packet_t ;
struct TYPE_17__ {scalar_t__ len; int /*<<< orphan*/  p; } ;
struct TYPE_20__ {TYPE_3__ buf; } ;
typedef  TYPE_6__ coap_option_t ;
struct TYPE_21__ {struct TYPE_21__* next; scalar_t__ name; } ;
typedef  TYPE_7__ coap_luser_entry ;
struct TYPE_22__ {TYPE_2__* user_entry; TYPE_1__* path; } ;
typedef  TYPE_8__ coap_endpoint_t ;
struct TYPE_16__ {TYPE_7__* next; } ;
struct TYPE_15__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_CONTENTTYPE_NONE ; 
 int /*<<< orphan*/  COAP_CONTENTTYPE_TEXT_PLAIN ; 
 int /*<<< orphan*/  COAP_OPTION_URI_PATH ; 
 int /*<<< orphan*/  COAP_RSPCODE_CONTENT ; 
 int /*<<< orphan*/  COAP_RSPCODE_NOT_FOUND ; 
 scalar_t__ LUA_TFUNCTION ; 
 size_t MAX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 TYPE_6__* coap_findOptions (TYPE_5__ const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int coap_make_response (int /*<<< orphan*/ *,TYPE_5__*,char const*,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static int handle_post_function(const coap_endpoint_t *ep, coap_rw_buffer_t *scratch, const coap_packet_t *inpkt, coap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo)
{
    const coap_option_t *opt;
    uint8_t count;
    int n;
    lua_State *L = lua_getstate();
    if (NULL != (opt = coap_findOptions(inpkt, COAP_OPTION_URI_PATH, &count)))
    {
        if ((count != ep->path->count ) && (count != ep->path->count + 1)) // +1 for /f/[function], /v/[variable]
        {
            NODE_DBG("should never happen.\n");
            goto end;
        }
        if (count == ep->path->count + 1)
        {
            coap_luser_entry *h = ep->user_entry->next;     // ->next: skip the first entry(head)
            while(NULL != h){
                if (opt[count-1].buf.len != strlen(h->name))
                {
                    h = h->next;
                    continue;
                }
                if (0 == memcmp(h->name, opt[count-1].buf.p, opt[count-1].buf.len))
                {
                    NODE_DBG("/v1/f/");
                    NODE_DBG((char *)h->name);
                    NODE_DBG(" match.\n");

                    if(strlen(h->name))
                    {
                        n = lua_gettop(L);
                        lua_getglobal(L, h->name);
                        if (lua_type(L, -1) != LUA_TFUNCTION) {
                            NODE_DBG ("should be a function\n");
                            lua_settop(L, n);
                            return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_NOT_FOUND, COAP_CONTENTTYPE_NONE);
                        } else {
                            lua_pushlstring(L, inpkt->payload.p, inpkt->payload.len);     // make sure payload.p is filled with '\0' after payload.len, or use lua_pushlstring
                            lua_call(L, 1, 1);
                            if (!lua_isnil(L, -1)){  /* get return? */
                                if( lua_isstring(L, -1) )   // deal with the return string
                                {
                                    size_t len = 0;
                                    const char *ret = luaL_checklstring( L, -1, &len );
                                    if(len > MAX_PAYLOAD_SIZE){
                                        lua_settop(L, n);
                                        luaL_error( L, "return string:<MAX_PAYLOAD_SIZE" );
                                        return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_NOT_FOUND, COAP_CONTENTTYPE_NONE);
                                    }
                                    NODE_DBG((char *)ret);
                                    NODE_DBG("\n");
                                    lua_settop(L, n);
                                    return coap_make_response(scratch, outpkt, ret, len, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_TEXT_PLAIN);
                                }
                            } else {
                                lua_settop(L, n);
                                return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_CONTENT, COAP_CONTENTTYPE_TEXT_PLAIN);
                            }
                        }
                    }
                } else {
                    h = h->next;
                }
            }
        }else{
            NODE_DBG("/v1/f match.\n");
            goto end;
        }
    }
    NODE_DBG("none match.\n");
end:
    return coap_make_response(scratch, outpkt, NULL, 0, id_hi, id_lo, &inpkt->tok, COAP_RSPCODE_NOT_FOUND, COAP_CONTENTTYPE_NONE);
}