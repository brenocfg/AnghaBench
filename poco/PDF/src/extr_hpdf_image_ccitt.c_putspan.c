#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int code; unsigned int length; int runlen; } ;
typedef  TYPE_1__ tableentry ;
struct _HPDF_CCITT_Data {int dummy; } ;
typedef  int int32 ;
struct TYPE_6__ {unsigned int bit; int data; } ;
typedef  TYPE_2__ HPDF_Fax3CodecState ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT (char*,int) ; 
 TYPE_2__* EncoderState (struct _HPDF_CCITT_Data*) ; 
 int /*<<< orphan*/  _PutBits (struct _HPDF_CCITT_Data*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
putspan(struct _HPDF_CCITT_Data *pData, int32 span, const tableentry* tab)
{
	HPDF_Fax3CodecState* sp = EncoderState(pData);
	unsigned int bit = sp->bit;
	int data = sp->data;
	unsigned int code, length;

	while (span >= 2624) {
		const tableentry* te = &tab[63 + (2560>>6)];
		code = te->code, length = te->length;
#ifdef FAX3_DEBUG
		DEBUG_PRINT("MakeUp", te->runlen);
#endif
		_PutBits(pData, code, length);
		span -= te->runlen;
	}
	if (span >= 64) {
		const tableentry* te = &tab[63 + (span>>6)];
		assert(te->runlen == 64*(span>>6));
		code = te->code, length = te->length;
#ifdef FAX3_DEBUG
		DEBUG_PRINT("MakeUp", te->runlen);
#endif
		_PutBits(pData, code, length);
		span -= te->runlen;
	}
	code = tab[span].code, length = tab[span].length;
#ifdef FAX3_DEBUG
	DEBUG_PRINT("  Term", tab[span].runlen);
#endif
	_PutBits(pData, code, length);

	sp->data = data;
	sp->bit = bit;
}