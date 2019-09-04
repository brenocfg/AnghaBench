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
typedef  int wchar_t ;
struct nls_table {int (* char2uni ) (unsigned char*,int,int*) ;unsigned char* charset2lower; } ;

/* Variables and functions */
 int stub1 (unsigned char*,int,int*) ; 
 int stub2 (unsigned char*,int,int*) ; 

__attribute__((used)) static inline int
fat_short2lower_uni(struct nls_table *t, unsigned char *c,
		    int clen, wchar_t *uni)
{
	int charlen;
	wchar_t wc;

	charlen = t->char2uni(c, clen, &wc);
	if (charlen < 0) {
		*uni = 0x003f;	/* a question mark */
		charlen = 1;
	} else if (charlen <= 1) {
		unsigned char nc = t->charset2lower[*c];

		if (!nc)
			nc = *c;

		charlen = t->char2uni(&nc, 1, uni);
		if (charlen < 0) {
			*uni = 0x003f;	/* a question mark */
			charlen = 1;
		}
	} else
		*uni = wc;

	return charlen;
}