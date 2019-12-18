#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gc_arena {int dummy; } ;
struct buffer {int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {size_t st_size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ platform_stat_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPTR (struct buffer*) ; 
 struct buffer alloc_buf_gc (size_t const,struct gc_arena*) ; 
 int /*<<< orphan*/  buf_inc_len (struct buffer*,scalar_t__) ; 
 int /*<<< orphan*/  buf_null_terminate (struct buffer*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (int /*<<< orphan*/ ,int,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_buf_gc (struct buffer*,struct gc_arena*) ; 
 int /*<<< orphan*/ * platform_fopen (char const*,char*) ; 
 scalar_t__ platform_stat (char const*,TYPE_1__*) ; 

struct buffer
buffer_read_from_file(const char *filename, struct gc_arena *gc)
{
    struct buffer ret = { 0 };

    platform_stat_t file_stat = {0};
    if (platform_stat(filename, &file_stat) < 0)
    {
        return ret;
    }

    FILE *fp = platform_fopen(filename, "r");
    if (!fp)
    {
        return ret;
    }

    const size_t size = file_stat.st_size;
    ret = alloc_buf_gc(size + 1, gc); /* space for trailing \0 */
    ssize_t read_size = fread(BPTR(&ret), 1, size, fp);
    if (read_size < 0)
    {
        free_buf_gc(&ret, gc);
        goto cleanup;
    }
    ASSERT(buf_inc_len(&ret, read_size));
    buf_null_terminate(&ret);

cleanup:
    fclose(fp);
    return ret;
}