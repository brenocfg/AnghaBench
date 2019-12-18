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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int seek_set(int fd, off_t pos) {
	return ((fd == -1) || (lseek (fd, (off_t) pos, SEEK_SET) == -1))? 0:1;
}