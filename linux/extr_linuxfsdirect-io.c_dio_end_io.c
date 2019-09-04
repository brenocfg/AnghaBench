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
struct dio {scalar_t__ is_async; } ;
struct bio {struct dio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dio_bio_end_aio (struct bio*) ; 
 int /*<<< orphan*/  dio_bio_end_io (struct bio*) ; 

void dio_end_io(struct bio *bio)
{
	struct dio *dio = bio->bi_private;

	if (dio->is_async)
		dio_bio_end_aio(bio);
	else
		dio_bio_end_io(bio);
}