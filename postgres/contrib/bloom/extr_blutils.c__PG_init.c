#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* optname; void* offset; void* opttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  BloomOptions ; 
 int /*<<< orphan*/  DEFAULT_BLOOM_BITS ; 
 int /*<<< orphan*/  DEFAULT_BLOOM_LENGTH ; 
 int INDEX_MAX_KEYS ; 
 int /*<<< orphan*/  MAX_BLOOM_BITS ; 
 int /*<<< orphan*/  MAX_BLOOM_LENGTH ; 
 char* MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 void* RELOPT_TYPE_INT ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  add_int_reloption (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_reloption_kind () ; 
 int /*<<< orphan*/ * bitSize ; 
 int /*<<< orphan*/  bl_relopt_kind ; 
 TYPE_1__* bl_relopt_tab ; 
 int /*<<< orphan*/  bloomLength ; 
 void* offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void
_PG_init(void)
{
	int			i;
	char		buf[16];

	bl_relopt_kind = add_reloption_kind();

	/* Option for length of signature */
	add_int_reloption(bl_relopt_kind, "length",
					  "Length of signature in bits",
					  DEFAULT_BLOOM_LENGTH, 1, MAX_BLOOM_LENGTH,
					  AccessExclusiveLock);
	bl_relopt_tab[0].optname = "length";
	bl_relopt_tab[0].opttype = RELOPT_TYPE_INT;
	bl_relopt_tab[0].offset = offsetof(BloomOptions, bloomLength);

	/* Number of bits for each possible index column: col1, col2, ... */
	for (i = 0; i < INDEX_MAX_KEYS; i++)
	{
		snprintf(buf, sizeof(buf), "col%d", i + 1);
		add_int_reloption(bl_relopt_kind, buf,
						  "Number of bits generated for each index column",
						  DEFAULT_BLOOM_BITS, 1, MAX_BLOOM_BITS,
						  AccessExclusiveLock);
		bl_relopt_tab[i + 1].optname = MemoryContextStrdup(TopMemoryContext,
														   buf);
		bl_relopt_tab[i + 1].opttype = RELOPT_TYPE_INT;
		bl_relopt_tab[i + 1].offset = offsetof(BloomOptions, bitSize[0]) + sizeof(int) * i;
	}
}