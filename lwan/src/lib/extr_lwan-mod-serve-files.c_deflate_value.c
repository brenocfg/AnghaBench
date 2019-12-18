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
struct lwan_value {unsigned long len; int /*<<< orphan*/ * value; } ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 scalar_t__ Z_OK ; 
 scalar_t__ compress (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long compressBound (unsigned long) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ is_compression_worthy (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * malloc (unsigned long const) ; 
 void realloc_if_needed (struct lwan_value*,unsigned long const) ; 

__attribute__((used)) static void deflate_value(const struct lwan_value *uncompressed,
                          struct lwan_value *compressed)
{
    const unsigned long bound = compressBound(uncompressed->len);

    compressed->len = bound;

    if (UNLIKELY(!(compressed->value = malloc(bound))))
        goto error_zero_out;

    if (UNLIKELY(compress((Bytef *)compressed->value, &compressed->len,
                          (Bytef *)uncompressed->value,
                          uncompressed->len) != Z_OK))
        goto error_free_compressed;

    if (is_compression_worthy(compressed->len, uncompressed->len))
        return realloc_if_needed(compressed, bound);

error_free_compressed:
    free(compressed->value);
    compressed->value = NULL;
error_zero_out:
    compressed->len = 0;
}