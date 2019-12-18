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
typedef  int /*<<< orphan*/  nsChannelBSC ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSCallback ;

/* Variables and functions */
 int /*<<< orphan*/ * nsChannelBSC_from_BSCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_stream_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT nsChannelBSC_read_data(BSCallback *bsc, IStream *stream)
{
    nsChannelBSC *This = nsChannelBSC_from_BSCallback(bsc);

    return read_stream_data(This, stream);
}