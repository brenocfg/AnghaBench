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
struct swap_map_handle {int dummy; } ;
struct snapshot_handle {scalar_t__ sync_read; } ;
struct hib_bio_batch {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ENODATA ; 
 int clean_pages_on_read ; 
 int /*<<< orphan*/  data_of (struct snapshot_handle) ; 
 int /*<<< orphan*/  hib_init_batch (struct hib_bio_batch*) ; 
 int hib_wait_io (struct hib_bio_batch*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  snapshot_image_loaded (struct snapshot_handle*) ; 
 int /*<<< orphan*/  snapshot_write_finalize (struct snapshot_handle*) ; 
 int snapshot_write_next (struct snapshot_handle*) ; 
 int swap_read_page (struct swap_map_handle*,int /*<<< orphan*/ ,struct hib_bio_batch*) ; 
 int /*<<< orphan*/  swsusp_show_speed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,char*) ; 

__attribute__((used)) static int load_image(struct swap_map_handle *handle,
                      struct snapshot_handle *snapshot,
                      unsigned int nr_to_read)
{
	unsigned int m;
	int ret = 0;
	ktime_t start;
	ktime_t stop;
	struct hib_bio_batch hb;
	int err2;
	unsigned nr_pages;

	hib_init_batch(&hb);

	clean_pages_on_read = true;
	pr_info("Loading image data pages (%u pages)...\n", nr_to_read);
	m = nr_to_read / 10;
	if (!m)
		m = 1;
	nr_pages = 0;
	start = ktime_get();
	for ( ; ; ) {
		ret = snapshot_write_next(snapshot);
		if (ret <= 0)
			break;
		ret = swap_read_page(handle, data_of(*snapshot), &hb);
		if (ret)
			break;
		if (snapshot->sync_read)
			ret = hib_wait_io(&hb);
		if (ret)
			break;
		if (!(nr_pages % m))
			pr_info("Image loading progress: %3d%%\n",
				nr_pages / m * 10);
		nr_pages++;
	}
	err2 = hib_wait_io(&hb);
	stop = ktime_get();
	if (!ret)
		ret = err2;
	if (!ret) {
		pr_info("Image loading done\n");
		snapshot_write_finalize(snapshot);
		if (!snapshot_image_loaded(snapshot))
			ret = -ENODATA;
	}
	swsusp_show_speed(start, stop, nr_to_read, "Read");
	return ret;
}