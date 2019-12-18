#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  val ;
struct TYPE_2__ {char* s; struct switch_val* link; struct switch_val* ports; void* i; } ;
struct switch_val {int port_vlan; int len; int duplex; int aneg; TYPE_1__ value; void* speed; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct switch_port_link {int port_vlan; int len; int duplex; int aneg; TYPE_1__ value; void* speed; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct switch_port {int port_vlan; int len; int duplex; int aneg; TYPE_1__ value; void* speed; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct switch_dev {int ports; } ;
struct switch_attr {int type; } ;

/* Variables and functions */
#define  CMD_ANEG 136 
#define  CMD_DUPLEX 135 
#define  CMD_NONE 134 
#define  CMD_SPEED 133 
#define  SWITCH_TYPE_INT 132 
#define  SWITCH_TYPE_LINK 131 
#define  SWITCH_TYPE_NOVAL 130 
#define  SWITCH_TYPE_PORTS 129 
#define  SWITCH_TYPE_STRING 128 
 int /*<<< orphan*/  SWLIB_PORT_FLAG_TAGGED ; 
 struct switch_val* alloca (int) ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 struct switch_val* malloc (int) ; 
 int /*<<< orphan*/  memset (struct switch_val*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 
 int swlib_set_attr (struct switch_dev*,struct switch_attr*,struct switch_val*) ; 

int swlib_set_attr_string(struct switch_dev *dev, struct switch_attr *a, int port_vlan, const char *str)
{
	struct switch_port *ports;
	struct switch_port_link *link;
	struct switch_val val;
	char *ptr;
	int cmd = CMD_NONE;

	memset(&val, 0, sizeof(val));
	val.port_vlan = port_vlan;
	switch(a->type) {
	case SWITCH_TYPE_INT:
		val.value.i = atoi(str);
		break;
	case SWITCH_TYPE_STRING:
		val.value.s = (char *)str;
		break;
	case SWITCH_TYPE_PORTS:
		ports = alloca(sizeof(struct switch_port) * dev->ports);
		memset(ports, 0, sizeof(struct switch_port) * dev->ports);
		val.len = 0;
		ptr = (char *)str;
		while(ptr && *ptr)
		{
			while(*ptr && isspace(*ptr))
				ptr++;

			if (!*ptr)
				break;

			if (!isdigit(*ptr))
				return -1;

			if (val.len >= dev->ports)
				return -1;

			ports[val.len].flags = 0;
			ports[val.len].id = strtoul(ptr, &ptr, 10);
			while(*ptr && !isspace(*ptr)) {
				if (*ptr == 't')
					ports[val.len].flags |= SWLIB_PORT_FLAG_TAGGED;
				else
					return -1;

				ptr++;
			}
			if (*ptr)
				ptr++;
			val.len++;
		}
		val.value.ports = ports;
		break;
	case SWITCH_TYPE_LINK:
		link = malloc(sizeof(struct switch_port_link));
		memset(link, 0, sizeof(struct switch_port_link));
		ptr = (char *)str;
		for (ptr = strtok(ptr," "); ptr; ptr = strtok(NULL, " ")) {
			switch (cmd) {
			case CMD_NONE:
				if (!strcmp(ptr, "duplex"))
					cmd = CMD_DUPLEX;
				else if (!strcmp(ptr, "autoneg"))
					cmd = CMD_ANEG;
				else if (!strcmp(ptr, "speed"))
					cmd = CMD_SPEED;
				else
					fprintf(stderr, "Unsupported option %s\n", ptr);
				break;
			case CMD_DUPLEX:
				if (!strcmp(ptr, "half"))
					link->duplex = 0;
				else if (!strcmp(ptr, "full"))
					link->duplex = 1;
				else
					fprintf(stderr, "Unsupported value %s\n", ptr);
				cmd = CMD_NONE;
				break;
			case CMD_ANEG:
				if (!strcmp(ptr, "on"))
					link->aneg = 1;
				else if (!strcmp(ptr, "off"))
					link->aneg = 0;
				else
					fprintf(stderr, "Unsupported value %s\n", ptr);
				cmd = CMD_NONE;
				break;
			case CMD_SPEED:
				link->speed = atoi(ptr);
				cmd = CMD_NONE;
				break;
			}
		}
		val.value.link = link;
		break;
	case SWITCH_TYPE_NOVAL:
		if (str && !strcmp(str, "0"))
			return 0;

		break;
	default:
		return -1;
	}
	return swlib_set_attr(dev, a, &val);
}