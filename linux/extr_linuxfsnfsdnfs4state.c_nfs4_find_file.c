#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs4_stid {int sc_type; TYPE_1__* sc_file; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fi_deleg_file; } ;

/* Variables and functions */
#define  NFS4_DELEG_STID 130 
#define  NFS4_LOCK_STID 129 
#define  NFS4_OPEN_STID 128 
 int RD_STATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct file* find_readable_file (TYPE_1__*) ; 
 struct file* find_writeable_file (TYPE_1__*) ; 
 struct file* get_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct file *
nfs4_find_file(struct nfs4_stid *s, int flags)
{
	if (!s)
		return NULL;

	switch (s->sc_type) {
	case NFS4_DELEG_STID:
		if (WARN_ON_ONCE(!s->sc_file->fi_deleg_file))
			return NULL;
		return get_file(s->sc_file->fi_deleg_file);
	case NFS4_OPEN_STID:
	case NFS4_LOCK_STID:
		if (flags & RD_STATE)
			return find_readable_file(s->sc_file);
		else
			return find_writeable_file(s->sc_file);
		break;
	}

	return NULL;
}