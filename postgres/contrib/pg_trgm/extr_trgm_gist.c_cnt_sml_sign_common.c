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
typedef  int /*<<< orphan*/  trgm ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  TRGM ;
typedef  int /*<<< orphan*/  BITVECP ;

/* Variables and functions */
 scalar_t__ ARRNELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPTRGM (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GETARR (int /*<<< orphan*/ *) ; 
 scalar_t__ GETBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASHVAL (scalar_t__) ; 

__attribute__((used)) static int32
cnt_sml_sign_common(TRGM *qtrg, BITVECP sign)
{
	int32		count = 0;
	int32		k,
				len = ARRNELEM(qtrg);
	trgm	   *ptr = GETARR(qtrg);
	int32		tmp = 0;

	for (k = 0; k < len; k++)
	{
		CPTRGM(((char *) &tmp), ptr + k);
		count += GETBIT(sign, HASHVAL(tmp));
	}

	return count;
}