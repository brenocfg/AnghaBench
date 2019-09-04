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
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  ofs; } ;
typedef  TYPE_1__ zend_elf_sectheader ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  efree (void*) ; 
 void* emalloc (scalar_t__) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,void*,scalar_t__) ; 

__attribute__((used)) static void* zend_elf_read_sect(int fd, zend_elf_sectheader *sect)
{
	void *s = emalloc(sect->size);

	if (lseek(fd, sect->ofs, SEEK_SET) < 0) {
		efree(s);
		return NULL;
	}
	if (read(fd, s, sect->size) != (ssize_t)sect->size) {
		efree(s);
		return NULL;
	}

	return s;
}