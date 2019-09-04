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
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {char* name; struct TYPE_8__* next; } ;
typedef  TYPE_3__ coap_luser_entry ;
struct TYPE_9__ {char* core_attr; TYPE_2__* path; TYPE_1__* user_entry; int /*<<< orphan*/ * handler; } ;
typedef  TYPE_4__ coap_endpoint_t ;
struct TYPE_7__ {int count; char** elems; } ;
struct TYPE_6__ {TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ c_strlen (char*) ; 
 int /*<<< orphan*/  c_strncat (char*,char*,scalar_t__) ; 
 TYPE_4__* endpoints ; 

void build_well_known_rsp(char *rsp, uint16_t rsplen)
{
    const coap_endpoint_t *ep = endpoints;
    int i;
    uint16_t len = rsplen;

    c_memset(rsp, 0, len);

    len--; // Null-terminated string

    while(NULL != ep->handler)
    {
        if (NULL == ep->core_attr) {
            ep++;
            continue;
        }
        if (NULL == ep->user_entry){
            if (0 < c_strlen(rsp)) {
                c_strncat(rsp, ",", len);
                len--;
            }

            c_strncat(rsp, "<", len);
            len--;

            for (i = 0; i < ep->path->count; i++) {
                c_strncat(rsp, "/", len);
                len--;

                c_strncat(rsp, ep->path->elems[i], len);
                len -= c_strlen(ep->path->elems[i]);
            }

            c_strncat(rsp, ">;", len);
            len -= 2;

            c_strncat(rsp, ep->core_attr, len);
            len -= c_strlen(ep->core_attr);
        } else {
            coap_luser_entry *h = ep->user_entry->next;     // ->next: skip the first entry(head)
            while(NULL != h){
                if (0 < c_strlen(rsp)) {
                    c_strncat(rsp, ",", len);
                    len--;
                }

                c_strncat(rsp, "<", len);
                len--;

                for (i = 0; i < ep->path->count; i++) {
                    c_strncat(rsp, "/", len);
                    len--;

                    c_strncat(rsp, ep->path->elems[i], len);
                    len -= c_strlen(ep->path->elems[i]);
                }

                c_strncat(rsp, "/", len);
                len--;

                c_strncat(rsp, h->name, len);
                len -= c_strlen(h->name);

                c_strncat(rsp, ">;", len);
                len -= 2;

                c_strncat(rsp, ep->core_attr, len);
                len -= c_strlen(ep->core_attr);

                h = h->next;
            }
        }
        ep++;
    }
}