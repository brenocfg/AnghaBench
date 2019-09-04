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
struct spi_test {scalar_t__ transfer_count; size_t* iterate_len; int iterate_tx_align; int iterate_rx_align; int /*<<< orphan*/  description; } ;
struct spi_device {TYPE_1__* master; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int dma_alignment; } ;

/* Variables and functions */
 int E2BIG ; 
 int SPI_TEST_MAX_ITERATE ; 
 scalar_t__ SPI_TEST_MAX_TRANSFERS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int spi_test_run_iter (struct spi_device*,struct spi_test const*,void*,void*,size_t,size_t,size_t) ; 

int spi_test_run_test(struct spi_device *spi, const struct spi_test *test,
		      void *tx, void *rx)
{
	int idx_len;
	size_t len;
	size_t tx_align, rx_align;
	int ret;

	/* test for transfer limits */
	if (test->transfer_count >= SPI_TEST_MAX_TRANSFERS) {
		dev_err(&spi->dev,
			"%s: Exceeded max number of transfers with %i\n",
			test->description, test->transfer_count);
		return -E2BIG;
	}

	/* setting up some values in spi_message
	 * based on some settings in spi_master
	 * some of this can also get done in the run() method
	 */

	/* iterate over all the iterable values using macros
	 * (to make it a bit more readable...
	 */
#define FOR_EACH_ALIGNMENT(var)						\
	for (var = 0;							\
	    var < (test->iterate_##var ?				\
			(spi->master->dma_alignment ?			\
			 spi->master->dma_alignment :			\
			 test->iterate_##var) :				\
			1);						\
	    var++)

	for (idx_len = 0; idx_len < SPI_TEST_MAX_ITERATE &&
	     (len = test->iterate_len[idx_len]) != -1; idx_len++) {
		FOR_EACH_ALIGNMENT(tx_align) {
			FOR_EACH_ALIGNMENT(rx_align) {
				/* and run the iteration */
				ret = spi_test_run_iter(spi, test,
							tx, rx,
							len,
							tx_align,
							rx_align);
				if (ret)
					return ret;
			}
		}
	}

	return 0;
}