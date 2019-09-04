#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULong ;
struct TYPE_6__ {int* x; int wds; } ;
typedef  int Long ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 TYPE_1__* Balloc (int) ; 
 TYPE_1__* multadd (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Bigint *
s2b
#ifdef KR_headers
	(s, nd0, nd, y9, dplen) CONST char *s; int nd0, nd, dplen; ULong y9;
#else
	(const char *s, int nd0, int nd, ULong y9, int dplen)
#endif
{
	Bigint *b;
	int i, k;
	Long x, y;

	x = (nd + 8) / 9;
	for(k = 0, y = 1; x > y; y <<= 1, k++) ;
#ifdef Pack_32
	b = Balloc(k);
	b->x[0] = y9;
	b->wds = 1;
#else
	b = Balloc(k+1);
	b->x[0] = y9 & 0xffff;
	b->wds = (b->x[1] = y9 >> 16) ? 2 : 1;
#endif

	i = 9;
	if (9 < nd0) {
		s += 9;
		do b = multadd(b, 10, *s++ - '0');
			while(++i < nd0);
		s += dplen;
		}
	else
		s += dplen + 9;
	for(; i < nd; i++)
		b = multadd(b, 10, *s++ - '0');
	return b;
	}