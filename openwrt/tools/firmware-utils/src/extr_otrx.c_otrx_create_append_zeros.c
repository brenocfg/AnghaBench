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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t EIO ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  trx_path ; 

__attribute__((used)) static ssize_t otrx_create_append_zeros(FILE *trx, size_t length) {
	uint8_t *buf;

	buf = malloc(length);
	if (!buf)
		return -ENOMEM;
	memset(buf, 0, length);

	if (fwrite(buf, 1, length, trx) != length) {
		fprintf(stderr, "Couldn't write %zu B to %s\n", length, trx_path);
		free(buf);
		return -EIO;
	}

	free(buf);

	return length;
}