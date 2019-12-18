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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  STT_FUNC ; 
 int /*<<< orphan*/  STT_OBJECT ; 
 char tolower (char) ; 

u8 kallsyms2elf_type(char type)
{
	type = tolower(type);
	return (type == 't' || type == 'w') ? STT_FUNC : STT_OBJECT;
}