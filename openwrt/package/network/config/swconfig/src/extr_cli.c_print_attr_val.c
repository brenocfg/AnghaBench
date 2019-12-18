#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i; char* s; struct switch_port_link* link; TYPE_1__* ports; } ;
struct switch_val {int len; int port_vlan; TYPE_2__ value; } ;
struct switch_port_link {int eee; int /*<<< orphan*/  rx_flow; int /*<<< orphan*/  tx_flow; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  aneg; int /*<<< orphan*/  link; } ;
struct switch_attr {int type; } ;
struct TYPE_3__ {int id; int flags; } ;

/* Variables and functions */
#define  SWITCH_TYPE_INT 131 
#define  SWITCH_TYPE_LINK 130 
#define  SWITCH_TYPE_PORTS 129 
#define  SWITCH_TYPE_STRING 128 
 int SWLIB_LINK_FLAG_EEE_1000BASET ; 
 int SWLIB_LINK_FLAG_EEE_100BASET ; 
 int SWLIB_PORT_FLAG_TAGGED ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* speed_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_attr_val(const struct switch_attr *attr, const struct switch_val *val)
{
	struct switch_port_link *link;
	int i;

	switch (attr->type) {
	case SWITCH_TYPE_INT:
		printf("%d", val->value.i);
		break;
	case SWITCH_TYPE_STRING:
		printf("%s", val->value.s);
		break;
	case SWITCH_TYPE_PORTS:
		for(i = 0; i < val->len; i++) {
			printf("%d%s ",
				val->value.ports[i].id,
				(val->value.ports[i].flags &
				 SWLIB_PORT_FLAG_TAGGED) ? "t" : "");
		}
		break;
	case SWITCH_TYPE_LINK:
		link = val->value.link;
		if (link->link)
			printf("port:%d link:up speed:%s %s-duplex %s%s%s%s%s",
				val->port_vlan,
				speed_str(link->speed),
				link->duplex ? "full" : "half",
				link->tx_flow ? "txflow " : "",
				link->rx_flow ? "rxflow " : "",
				link->eee & SWLIB_LINK_FLAG_EEE_100BASET ? "eee100 " : "",
				link->eee & SWLIB_LINK_FLAG_EEE_1000BASET ? "eee1000 " : "",
				link->aneg ? "auto" : "");
		else
			printf("port:%d link:down", val->port_vlan);
		break;
	default:
		printf("?unknown-type?");
	}
}