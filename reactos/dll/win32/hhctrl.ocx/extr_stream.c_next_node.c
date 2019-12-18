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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  strbuf_t ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  find_node_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stream_chr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 

BOOL next_node(stream_t *stream, strbuf_t *buf)
{
    /* find the beginning of the next node */
    if(!stream_chr(stream, NULL, '<'))
        return FALSE;

    /* read out the data of the next node */
    if(!find_node_end(stream, buf))
        return FALSE;

    strbuf_append(buf, ">", 2);

    return TRUE;
}