#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct svc_rqst {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int kstrtouint (char*,int,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static bool
numeric_name_to_id(struct svc_rqst *rqstp, int type, const char *name, u32 namelen, u32 *id)
{
	int ret;
	char buf[11];

	if (namelen + 1 > sizeof(buf))
		/* too long to represent a 32-bit id: */
		return false;
	/* Just to make sure it's null-terminated: */
	memcpy(buf, name, namelen);
	buf[namelen] = '\0';
	ret = kstrtouint(buf, 10, id);
	return ret == 0;
}