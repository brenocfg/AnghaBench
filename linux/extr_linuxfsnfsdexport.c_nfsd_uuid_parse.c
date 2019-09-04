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

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EX_UUID_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned char* kmemdup (char*,int,int /*<<< orphan*/ ) ; 
 int qword_get (char**,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
nfsd_uuid_parse(char **mesg, char *buf, unsigned char **puuid)
{
	int len;

	/* more than one uuid */
	if (*puuid)
		return -EINVAL;

	/* expect a 16 byte uuid encoded as \xXXXX... */
	len = qword_get(mesg, buf, PAGE_SIZE);
	if (len != EX_UUID_LEN)
		return -EINVAL;

	*puuid = kmemdup(buf, EX_UUID_LEN, GFP_KERNEL);
	if (*puuid == NULL)
		return -ENOMEM;

	return 0;
}