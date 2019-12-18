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
struct data {size_t len; scalar_t__ val; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_NONE ; 
 struct data data_add_marker (struct data,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct data data_grow_for (struct data,size_t) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 struct data empty_data ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (scalar_t__,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

struct data data_copy_file(FILE *f, size_t maxlen)
{
	struct data d = empty_data;

	d = data_add_marker(d, TYPE_NONE, NULL);
	while (!feof(f) && (d.len < maxlen)) {
		size_t chunksize, ret;

		if (maxlen == -1)
			chunksize = 4096;
		else
			chunksize = maxlen - d.len;

		d = data_grow_for(d, chunksize);
		ret = fread(d.val + d.len, 1, chunksize, f);

		if (ferror(f))
			die("Error reading file into data: %s", strerror(errno));

		if (d.len + ret < d.len)
			die("Overflow reading file into data\n");

		d.len += ret;
	}

	return d;
}