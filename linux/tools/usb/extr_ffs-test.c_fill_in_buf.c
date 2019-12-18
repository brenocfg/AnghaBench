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
struct thread {int dummy; } ;
typedef  size_t ssize_t ;
typedef  size_t __u8 ;

/* Variables and functions */
#define  PAT_PIPE 130 
#define  PAT_SEQ 129 
#define  PAT_ZERO 128 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int pattern ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static ssize_t
fill_in_buf(struct thread *ignore, void *buf, size_t nbytes)
{
	size_t i;
	__u8 *p;

	(void)ignore;

	switch (pattern) {
	case PAT_ZERO:
		memset(buf, 0, nbytes);
		break;

	case PAT_SEQ:
		for (p = buf, i = 0; i < nbytes; ++i, ++p)
			*p = i % 63;
		break;

	case PAT_PIPE:
		return fread(buf, 1, nbytes, stdin);
	}

	return nbytes;
}