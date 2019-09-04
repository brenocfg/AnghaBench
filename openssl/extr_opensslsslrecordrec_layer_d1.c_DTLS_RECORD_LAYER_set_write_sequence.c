#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  write_sequence; } ;
typedef  TYPE_1__ RECORD_LAYER ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_NUM_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

void DTLS_RECORD_LAYER_set_write_sequence(RECORD_LAYER *rl, unsigned char *seq)
{
    memcpy(rl->write_sequence, seq, SEQ_NUM_SIZE);
}