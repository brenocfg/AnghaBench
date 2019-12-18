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
typedef  int umode_t ;

/* Variables and functions */
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int const S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 size_t TOMOYO_TYPE_IS_BLOCK_DEV ; 
 size_t TOMOYO_TYPE_IS_CHAR_DEV ; 
 size_t TOMOYO_TYPE_IS_DIRECTORY ; 
 size_t TOMOYO_TYPE_IS_FIFO ; 
 size_t TOMOYO_TYPE_IS_FILE ; 
 size_t TOMOYO_TYPE_IS_SOCKET ; 
 size_t TOMOYO_TYPE_IS_SYMLINK ; 
 char const** tomoyo_condition_keyword ; 

__attribute__((used)) static inline const char *tomoyo_filetype(const umode_t mode)
{
	switch (mode & S_IFMT) {
	case S_IFREG:
	case 0:
		return tomoyo_condition_keyword[TOMOYO_TYPE_IS_FILE];
	case S_IFDIR:
		return tomoyo_condition_keyword[TOMOYO_TYPE_IS_DIRECTORY];
	case S_IFLNK:
		return tomoyo_condition_keyword[TOMOYO_TYPE_IS_SYMLINK];
	case S_IFIFO:
		return tomoyo_condition_keyword[TOMOYO_TYPE_IS_FIFO];
	case S_IFSOCK:
		return tomoyo_condition_keyword[TOMOYO_TYPE_IS_SOCKET];
	case S_IFBLK:
		return tomoyo_condition_keyword[TOMOYO_TYPE_IS_BLOCK_DEV];
	case S_IFCHR:
		return tomoyo_condition_keyword[TOMOYO_TYPE_IS_CHAR_DEV];
	}
	return "unknown"; /* This should not happen. */
}