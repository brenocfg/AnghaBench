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
struct p9_fcall {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int p9pdu_writef (struct p9_fcall*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int p9pdu_prepare(struct p9_fcall *pdu, int16_t tag, int8_t type)
{
	pdu->id = type;
	return p9pdu_writef(pdu, 0, "dbw", 0, type, tag);
}