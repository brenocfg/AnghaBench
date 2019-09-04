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
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  int /*<<< orphan*/  RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  combine_sequences (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  place_single (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void place_sequence(const RAGraph *g, int l, const RGraphNode *bm, const RGraphNode *bp, int from_up, int va, int vr) {
	if (vr == va + 1) {
		place_single (g, l, bm, bp, from_up, va);
	} else if (vr > va + 1) {
		int vt = (vr + va) / 2;
		place_sequence (g, l, bm, bp, from_up, va, vt);
		place_sequence (g, l, bm, bp, from_up, vt, vr);
		combine_sequences (g, l, bm, bp, from_up, va, vr);
	}
}