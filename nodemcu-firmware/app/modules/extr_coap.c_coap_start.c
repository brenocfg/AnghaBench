#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* udp; } ;
struct espconn {TYPE_2__ proto; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {scalar_t__ self_ref; struct espconn* pesp_conn; } ;
typedef  TYPE_3__ lcoap_userdata ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_4__ ip_addr_t ;
struct TYPE_6__ {unsigned int local_port; int /*<<< orphan*/  local_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPSTR ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  coap_received ; 
 int /*<<< orphan*/  coap_sent ; 
 int /*<<< orphan*/  espconn_create (struct espconn*) ; 
 int /*<<< orphan*/  espconn_regist_recvcb (struct espconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  espconn_regist_sentcb (struct espconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaddr_addr (char const*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,TYPE_3__*,int,char*) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int coap_start( lua_State* L, const char* mt )
{
  struct espconn *pesp_conn = NULL;
  lcoap_userdata *cud;
  unsigned port;
  size_t il;
  ip_addr_t ipaddr;

  cud = (lcoap_userdata *)luaL_checkudata(L, 1, mt);
  luaL_argcheck(L, cud, 1, "Server/Client expected");
  if(cud==NULL){
    NODE_DBG("userdata is nil.\n");
    return 0;
  }

  pesp_conn = cud->pesp_conn;
  port = luaL_checkinteger( L, 2 );
  pesp_conn->proto.udp->local_port = port;
  NODE_DBG("UDP port is set: %d.\n", port);

  if( lua_isstring(L,3) )   // deal with the ip string
  {
    const char *ip = luaL_checklstring( L, 3, &il );
    if (ip == NULL)
    {
      ip = "0.0.0.0";
    }
    ipaddr.addr = ipaddr_addr(ip);
    memcpy(pesp_conn->proto.udp->local_ip, &ipaddr.addr, 4);
    NODE_DBG("UDP ip is set: ");
    NODE_DBG(IPSTR, IP2STR(&ipaddr.addr));
    NODE_DBG("\n");
  }

  if(LUA_NOREF==cud->self_ref){
    lua_pushvalue(L, 1);  // copy to the top of stack
    cud->self_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }

  espconn_regist_recvcb(pesp_conn, coap_received);
  espconn_regist_sentcb(pesp_conn, coap_sent);
  espconn_create(pesp_conn);

  NODE_DBG("Coap Server started on port: %d\n", port);
  NODE_DBG("coap_start is called.\n");
  return 0;
}