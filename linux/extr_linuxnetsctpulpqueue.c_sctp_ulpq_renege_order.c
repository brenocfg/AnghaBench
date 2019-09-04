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
struct sctp_ulpq {int /*<<< orphan*/  lobby; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_ulpq_renege_list (struct sctp_ulpq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u16 sctp_ulpq_renege_order(struct sctp_ulpq *ulpq, __u16 needed)
{
	return sctp_ulpq_renege_list(ulpq, &ulpq->lobby, needed);
}