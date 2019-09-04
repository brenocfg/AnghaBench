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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CEPH_O_CREAT ; 
 int CEPH_O_DIRECTORY ; 
 int CEPH_O_EXCL ; 
 int CEPH_O_NOFOLLOW ; 
 int CEPH_O_RDONLY ; 
 int CEPH_O_RDWR ; 
 int CEPH_O_TRUNC ; 
 int CEPH_O_WRONLY ; 
 int O_ACCMODE ; 
 int O_CREAT ; 
 int O_DIRECTORY ; 
 int O_EXCL ; 
 int O_NOFOLLOW ; 
#define  O_RDONLY 130 
#define  O_RDWR 129 
 int O_TRUNC ; 
#define  O_WRONLY 128 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dout (char*,int) ; 

__attribute__((used)) static __le32 ceph_flags_sys2wire(u32 flags)
{
	u32 wire_flags = 0;

	switch (flags & O_ACCMODE) {
	case O_RDONLY:
		wire_flags |= CEPH_O_RDONLY;
		break;
	case O_WRONLY:
		wire_flags |= CEPH_O_WRONLY;
		break;
	case O_RDWR:
		wire_flags |= CEPH_O_RDWR;
		break;
	}

	flags &= ~O_ACCMODE;

#define ceph_sys2wire(a) if (flags & a) { wire_flags |= CEPH_##a; flags &= ~a; }

	ceph_sys2wire(O_CREAT);
	ceph_sys2wire(O_EXCL);
	ceph_sys2wire(O_TRUNC);
	ceph_sys2wire(O_DIRECTORY);
	ceph_sys2wire(O_NOFOLLOW);

#undef ceph_sys2wire

	if (flags)
		dout("unused open flags: %x\n", flags);

	return cpu_to_le32(wire_flags);
}