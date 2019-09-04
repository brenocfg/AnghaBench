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
struct fd {TYPE_1__* file; } ;
struct TYPE_2__ {int f_mode; } ;

/* Variables and functions */
 int EBADF ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int READ ; 
 int WRITE ; 
 int /*<<< orphan*/  fdput (struct fd) ; 

__attribute__((used)) static int vmsplice_type(struct fd f, int *type)
{
	if (!f.file)
		return -EBADF;
	if (f.file->f_mode & FMODE_WRITE) {
		*type = WRITE;
	} else if (f.file->f_mode & FMODE_READ) {
		*type = READ;
	} else {
		fdput(f);
		return -EBADF;
	}
	return 0;
}