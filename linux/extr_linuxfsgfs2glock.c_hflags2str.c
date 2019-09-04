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
typedef  int u16 ;

/* Variables and functions */
 int GL_ASYNC ; 
 int GL_EXACT ; 
 int GL_NOCACHE ; 
 int /*<<< orphan*/  HIF_FIRST ; 
 int /*<<< orphan*/  HIF_HOLDER ; 
 int /*<<< orphan*/  HIF_WAIT ; 
 int LM_FLAG_ANY ; 
 int LM_FLAG_NOEXP ; 
 int LM_FLAG_PRIORITY ; 
 int LM_FLAG_TRY ; 
 int LM_FLAG_TRY_1CB ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static const char *hflags2str(char *buf, u16 flags, unsigned long iflags)
{
	char *p = buf;
	if (flags & LM_FLAG_TRY)
		*p++ = 't';
	if (flags & LM_FLAG_TRY_1CB)
		*p++ = 'T';
	if (flags & LM_FLAG_NOEXP)
		*p++ = 'e';
	if (flags & LM_FLAG_ANY)
		*p++ = 'A';
	if (flags & LM_FLAG_PRIORITY)
		*p++ = 'p';
	if (flags & GL_ASYNC)
		*p++ = 'a';
	if (flags & GL_EXACT)
		*p++ = 'E';
	if (flags & GL_NOCACHE)
		*p++ = 'c';
	if (test_bit(HIF_HOLDER, &iflags))
		*p++ = 'H';
	if (test_bit(HIF_WAIT, &iflags))
		*p++ = 'W';
	if (test_bit(HIF_FIRST, &iflags))
		*p++ = 'F';
	*p = 0;
	return buf;
}