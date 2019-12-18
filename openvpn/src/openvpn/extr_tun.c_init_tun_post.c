#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tuntap_options {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  hEvent; } ;
struct TYPE_6__ {TYPE_2__ overlapped; } ;
struct TYPE_4__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct tuntap {int /*<<< orphan*/  adapter_index; TYPE_3__ writes; TYPE_1__ rw_handle; TYPE_3__ reads; struct tuntap_options options; } ;
struct frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TUN_ADAPTER_INDEX_INVALID ; 
 int /*<<< orphan*/  overlapped_io_init (TYPE_3__*,struct frame const*,int /*<<< orphan*/ ,int) ; 

void
init_tun_post(struct tuntap *tt,
              const struct frame *frame,
              const struct tuntap_options *options)
{
    tt->options = *options;
#ifdef _WIN32
    overlapped_io_init(&tt->reads, frame, FALSE, true);
    overlapped_io_init(&tt->writes, frame, TRUE, true);
    tt->rw_handle.read = tt->reads.overlapped.hEvent;
    tt->rw_handle.write = tt->writes.overlapped.hEvent;
    tt->adapter_index = TUN_ADAPTER_INDEX_INVALID;
#endif
}