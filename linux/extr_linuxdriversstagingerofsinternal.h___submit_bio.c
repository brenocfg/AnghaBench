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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static inline void __submit_bio(struct bio *bio, unsigned op, unsigned op_flags)
{
	bio_set_op_attrs(bio, op, op_flags);
	submit_bio(bio);
}