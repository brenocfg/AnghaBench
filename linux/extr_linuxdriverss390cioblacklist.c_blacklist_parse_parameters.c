#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ range_action ;
struct TYPE_9__ {unsigned int ssid; unsigned int devno; } ;
struct TYPE_10__ {TYPE_3__ dev_id; } ;
struct TYPE_7__ {unsigned int ssid; unsigned int devno; } ;
struct TYPE_8__ {TYPE_1__ dev_id; } ;
struct TYPE_11__ {TYPE_4__ fcp; TYPE_2__ ccw; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_5__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPL_TYPE_CCW ; 
 scalar_t__ IPL_TYPE_FCP ; 
 scalar_t__ IPL_TYPE_FCP_DUMP ; 
 unsigned int __MAX_CSSID ; 
 unsigned int __MAX_SSID ; 
 unsigned int __MAX_SUBCHANNEL ; 
 scalar_t__ add ; 
 int blacklist_range (scalar_t__,unsigned int,unsigned int,unsigned int,unsigned int,int) ; 
 int console_devno ; 
 scalar_t__ free ; 
 TYPE_6__ ipl_info ; 
 int parse_busid (char*,unsigned int*,unsigned int*,unsigned int*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int blacklist_parse_parameters(char *str, range_action action,
				      int msgtrigger)
{
	unsigned int from_cssid, to_cssid, from_ssid, to_ssid, from, to;
	int rc, totalrc;
	char *parm;
	range_action ra;

	totalrc = 0;

	while ((parm = strsep(&str, ","))) {
		rc = 0;
		ra = action;
		if (*parm == '!') {
			if (ra == add)
				ra = free;
			else
				ra = add;
			parm++;
		}
		if (strcmp(parm, "all") == 0) {
			from_cssid = 0;
			from_ssid = 0;
			from = 0;
			to_cssid = __MAX_CSSID;
			to_ssid = __MAX_SSID;
			to = __MAX_SUBCHANNEL;
		} else if (strcmp(parm, "ipldev") == 0) {
			if (ipl_info.type == IPL_TYPE_CCW) {
				from_cssid = 0;
				from_ssid = ipl_info.data.ccw.dev_id.ssid;
				from = ipl_info.data.ccw.dev_id.devno;
			} else if (ipl_info.type == IPL_TYPE_FCP ||
				   ipl_info.type == IPL_TYPE_FCP_DUMP) {
				from_cssid = 0;
				from_ssid = ipl_info.data.fcp.dev_id.ssid;
				from = ipl_info.data.fcp.dev_id.devno;
			} else {
				continue;
			}
			to_cssid = from_cssid;
			to_ssid = from_ssid;
			to = from;
		} else if (strcmp(parm, "condev") == 0) {
			if (console_devno == -1)
				continue;

			from_cssid = to_cssid = 0;
			from_ssid = to_ssid = 0;
			from = to = console_devno;
		} else {
			rc = parse_busid(strsep(&parm, "-"), &from_cssid,
					 &from_ssid, &from, msgtrigger);
			if (!rc) {
				if (parm != NULL)
					rc = parse_busid(parm, &to_cssid,
							 &to_ssid, &to,
							 msgtrigger);
				else {
					to_cssid = from_cssid;
					to_ssid = from_ssid;
					to = from;
				}
			}
		}
		if (!rc) {
			rc = blacklist_range(ra, from_ssid, to_ssid, from, to,
					     msgtrigger);
			if (rc)
				totalrc = -EINVAL;
		} else
			totalrc = -EINVAL;
	}

	return totalrc;
}