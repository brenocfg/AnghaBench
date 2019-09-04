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
struct seq_file {int dummy; } ;
struct ath_txq {int /*<<< orphan*/  pending_frames; int /*<<< orphan*/  axq_ampdu_depth; int /*<<< orphan*/  axq_depth; int /*<<< orphan*/  axq_qnum; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_txq_lock (struct ath_softc*,struct ath_txq*) ; 
 int /*<<< orphan*/  ath_txq_unlock (struct ath_softc*,struct ath_txq*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_queue(struct ath_softc *sc, struct ath_txq *txq,
			struct seq_file *file)
{
	ath_txq_lock(sc, txq);

	seq_printf(file, "%s: %d ", "qnum", txq->axq_qnum);
	seq_printf(file, "%s: %2d ", "qdepth", txq->axq_depth);
	seq_printf(file, "%s: %2d ", "ampdu-depth", txq->axq_ampdu_depth);
	seq_printf(file, "%s: %3d\n", "pending", txq->pending_frames);

	ath_txq_unlock(sc, txq);
}