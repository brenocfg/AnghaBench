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
union cmdret {unsigned char* retbytes; } ;
struct cmdif {int dummy; } ;

/* Variables and functions */
 union cmdret CMDRET_ZERO ; 
 int EIO ; 
 scalar_t__ SEND_RSSV (struct cmdif*,unsigned char,unsigned char,union cmdret*) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned char,unsigned char) ; 

__attribute__((used)) static int
getsourcesink(struct cmdif *cif, unsigned char source, unsigned char sink,
	      unsigned char *a, unsigned char *b)
{
	union cmdret rptr = CMDRET_ZERO;

	if (SEND_RSSV(cif, source, sink, &rptr) &&
	    SEND_RSSV(cif, source, sink, &rptr))
		return -EIO;
	*a = rptr.retbytes[0];
	*b = rptr.retbytes[1];
	snd_printdd("getsourcesink 0x%x 0x%x\n", *a, *b);
	return 0;
}