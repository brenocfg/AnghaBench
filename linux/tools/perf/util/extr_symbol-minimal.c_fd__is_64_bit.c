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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  e_ident ;

/* Variables and functions */
 size_t EI_CLASS ; 
 int EI_NIDENT ; 
 size_t EI_VERSION ; 
 scalar_t__ ELFCLASS64 ; 
 int /*<<< orphan*/  ELFMAG ; 
 scalar_t__ EV_CURRENT ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SELFMAG ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readn (int,scalar_t__*,int) ; 

__attribute__((used)) static int fd__is_64_bit(int fd)
{
	u8 e_ident[EI_NIDENT];

	if (lseek(fd, 0, SEEK_SET))
		return -1;

	if (readn(fd, e_ident, sizeof(e_ident)) != sizeof(e_ident))
		return -1;

	if (memcmp(e_ident, ELFMAG, SELFMAG) ||
	    e_ident[EI_VERSION] != EV_CURRENT)
		return -1;

	return e_ident[EI_CLASS] == ELFCLASS64;
}