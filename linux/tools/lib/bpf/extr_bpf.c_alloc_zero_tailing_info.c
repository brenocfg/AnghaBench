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
typedef  int __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *
alloc_zero_tailing_info(const void *orecord, __u32 cnt,
			__u32 actual_rec_size, __u32 expected_rec_size)
{
	__u64 info_len = actual_rec_size * cnt;
	void *info, *nrecord;
	int i;

	info = malloc(info_len);
	if (!info)
		return NULL;

	/* zero out bytes kernel does not understand */
	nrecord = info;
	for (i = 0; i < cnt; i++) {
		memcpy(nrecord, orecord, expected_rec_size);
		memset(nrecord + expected_rec_size, 0,
		       actual_rec_size - expected_rec_size);
		orecord += actual_rec_size;
		nrecord += actual_rec_size;
	}

	return info;
}