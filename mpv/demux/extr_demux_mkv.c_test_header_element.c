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
typedef  int /*<<< orphan*/  uint32_t ;
struct header_elem {int parsed; } ;
struct demuxer {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 struct header_elem* get_header_element (struct demuxer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool test_header_element(struct demuxer *demuxer, uint32_t id,
                                int64_t element_filepos)
{
    struct header_elem *elem = get_header_element(demuxer, id, element_filepos);
    if (!elem)
        return false;
    if (elem->parsed)
        return true;
    elem->parsed = true;
    return false;
}