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
typedef  int /*<<< orphan*/  u16 ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {void* no_formal_ino; void* no_addr; } ;
struct gfs2_dirent {int /*<<< orphan*/  __pad; void* de_type; void* de_name_len; void* de_rec_len; int /*<<< orphan*/  de_hash; TYPE_1__ de_inum; } ;

/* Variables and functions */
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct gfs2_dirent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void gfs2_qstr2dirent(const struct qstr *name, u16 reclen, struct gfs2_dirent *dent)
{
	dent->de_inum.no_addr = cpu_to_be64(0);
	dent->de_inum.no_formal_ino = cpu_to_be64(0);
	dent->de_hash = cpu_to_be32(name->hash);
	dent->de_rec_len = cpu_to_be16(reclen);
	dent->de_name_len = cpu_to_be16(name->len);
	dent->de_type = cpu_to_be16(0);
	memset(dent->__pad, 0, sizeof(dent->__pad));
	memcpy(dent + 1, name->name, name->len);
}