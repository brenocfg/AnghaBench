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
typedef  int /*<<< orphan*/  ZSTD_CStream ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createCStream () ; 
 int /*<<< orphan*/  ZSTD_freeCStream (int /*<<< orphan*/ *) ; 

int main(void)
{
	ZSTD_CStream	*cstream;

	cstream = ZSTD_createCStream();
	ZSTD_freeCStream(cstream);

	return 0;
}