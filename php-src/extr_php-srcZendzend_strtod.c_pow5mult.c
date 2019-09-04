#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* next; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 int /*<<< orphan*/  Bfree (TYPE_1__*) ; 
 TYPE_1__* i2b (int) ; 
 void* mult (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* multadd (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* p5s ; 

__attribute__((used)) static Bigint *
pow5mult
#ifdef KR_headers
	(b, k) Bigint *b; int k;
#else
	(Bigint *b, int k)
#endif
{
	Bigint *b1, *p5, *p51;
	int i;
	static int p05[3] = { 5, 25, 125 };

	if ((i = k & 3))
		b = multadd(b, p05[i-1], 0);

	if (!(k >>= 2))
		return b;
	if (!(p5 = p5s)) {
		/* first time */
#ifdef MULTIPLE_THREADS
		ACQUIRE_DTOA_LOCK(1);
		if (!(p5 = p5s)) {
			p5 = p5s = i2b(625);
			p5->next = 0;
			}
		FREE_DTOA_LOCK(1);
#else
		p5 = p5s = i2b(625);
		p5->next = 0;
#endif
		}
	for(;;) {
		if (k & 1) {
			b1 = mult(b, p5);
			Bfree(b);
			b = b1;
			}
		if (!(k >>= 1))
			break;
		if (!(p51 = p5->next)) {
#ifdef MULTIPLE_THREADS
			ACQUIRE_DTOA_LOCK(1);
			if (!(p51 = p5->next)) {
				p51 = p5->next = mult(p5,p5);
				p51->next = 0;
				}
			FREE_DTOA_LOCK(1);
#else
			p51 = p5->next = mult(p5,p5);
			p51->next = 0;
#endif
			}
		p5 = p51;
		}
	return b;
	}