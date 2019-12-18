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
struct magic {int str_flags; } ;

/* Variables and functions */
#define  PSTRING_1_LE 132 
#define  PSTRING_2_BE 131 
#define  PSTRING_2_LE 130 
#define  PSTRING_4_BE 129 
#define  PSTRING_4_LE 128 
 int PSTRING_LEN ; 
 int /*<<< orphan*/  abort () ; 

size_t
file_pstring_length_size(const struct magic *m)
{
	switch (m->str_flags & PSTRING_LEN) {
	case PSTRING_1_LE:
		return 1;
	case PSTRING_2_LE:
	case PSTRING_2_BE:
		return 2;
	case PSTRING_4_LE:
	case PSTRING_4_BE:
		return 4;
	default:
		abort();	/* Impossible */
		return 1;
	}
}