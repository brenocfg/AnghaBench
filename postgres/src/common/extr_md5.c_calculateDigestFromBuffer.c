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
typedef  int uint8 ;
typedef  int uint32 ;

/* Variables and functions */
 int* createPaddedCopyWithLength (int const*,int*) ; 
 int /*<<< orphan*/  doTheRounds (int*,int*) ; 
 int /*<<< orphan*/  free (int*) ; 

__attribute__((used)) static int
calculateDigestFromBuffer(const uint8 *b, uint32 len, uint8 sum[16])
{
	register uint32 i,
				j,
				k,
				newI;
	uint32		l;
	uint8	   *input;
	register uint32 *wbp;
	uint32		workBuff[16],
				state[4];

	l = len;

	state[0] = 0x67452301;
	state[1] = 0xEFCDAB89;
	state[2] = 0x98BADCFE;
	state[3] = 0x10325476;

	if ((input = createPaddedCopyWithLength(b, &l)) == NULL)
		return 0;

	for (i = 0;;)
	{
		if ((newI = i + 16 * 4) > l)
			break;
		k = i + 3;
		for (j = 0; j < 16; j++)
		{
			wbp = (workBuff + j);
			*wbp = input[k--];
			*wbp <<= 8;
			*wbp |= input[k--];
			*wbp <<= 8;
			*wbp |= input[k--];
			*wbp <<= 8;
			*wbp |= input[k];
			k += 7;
		}
		doTheRounds(workBuff, state);
		i = newI;
	}
	free(input);

	j = 0;
	for (i = 0; i < 4; i++)
	{
		k = state[i];
		sum[j++] = (k & 0xff);
		k >>= 8;
		sum[j++] = (k & 0xff);
		k >>= 8;
		sum[j++] = (k & 0xff);
		k >>= 8;
		sum[j++] = (k & 0xff);
	}
	return 1;
}