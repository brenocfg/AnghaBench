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
 int PSTRING_LENGTH_INCLUDES_ITSELF ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ file_pstring_length_size (struct magic const*) ; 

size_t
file_pstring_get_length(const struct magic *m, const char *ss)
{
	size_t len = 0;
	const unsigned char *s = (const unsigned char *)ss;
	unsigned int s3, s2, s1, s0;

	switch (m->str_flags & PSTRING_LEN) {
	case PSTRING_1_LE:
		len = *s;
		break;
	case PSTRING_2_LE:
		s0 = s[0];
		s1 = s[1];
		len = (s1 << 8) | s0;
		break;
	case PSTRING_2_BE:
		s0 = s[0];
		s1 = s[1];
		len = (s0 << 8) | s1;
		break;
	case PSTRING_4_LE:
		s0 = s[0];
		s1 = s[1];
		s2 = s[2];
		s3 = s[3];
		len = (s3 << 24) | (s2 << 16) | (s1 << 8) | s0;
		break;
	case PSTRING_4_BE:
		s0 = s[0];
		s1 = s[1];
		s2 = s[2];
		s3 = s[3];
		len = (s0 << 24) | (s1 << 16) | (s2 << 8) | s3;
		break;
	default:
		abort();	/* Impossible */
	}

	if (m->str_flags & PSTRING_LENGTH_INCLUDES_ITSELF)
		len -= file_pstring_length_size(m);

	return len;
}