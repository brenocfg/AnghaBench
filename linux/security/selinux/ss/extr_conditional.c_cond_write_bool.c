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
struct policy_data {void* fp; } ;
struct cond_bool_datum {int value; int state; } ;
typedef  char __le32 ;

/* Variables and functions */
 char cpu_to_le32 (int) ; 
 int put_entry (char*,int,int,void*) ; 
 int strlen (char*) ; 

int cond_write_bool(void *vkey, void *datum, void *ptr)
{
	char *key = vkey;
	struct cond_bool_datum *booldatum = datum;
	struct policy_data *pd = ptr;
	void *fp = pd->fp;
	__le32 buf[3];
	u32 len;
	int rc;

	len = strlen(key);
	buf[0] = cpu_to_le32(booldatum->value);
	buf[1] = cpu_to_le32(booldatum->state);
	buf[2] = cpu_to_le32(len);
	rc = put_entry(buf, sizeof(u32), 3, fp);
	if (rc)
		return rc;
	rc = put_entry(key, 1, len, fp);
	if (rc)
		return rc;
	return 0;
}