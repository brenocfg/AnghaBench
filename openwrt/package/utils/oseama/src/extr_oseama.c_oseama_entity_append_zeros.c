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
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  seama_path ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static ssize_t oseama_entity_append_zeros(FILE *seama, size_t length) {
	uint8_t *buf;

	buf = malloc(length);
	if (!buf)
		return -ENOMEM;
	memset(buf, 0, length);

	if (fwrite(buf, 1, length, seama) != length) {
		fprintf(stderr, "Couldn't write %zu B to %s\n", length, seama_path);
		return -EIO;
	}

	return length;
}