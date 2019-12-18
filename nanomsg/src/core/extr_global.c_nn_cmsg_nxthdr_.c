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
struct nn_msghdr {size_t msg_controllen; scalar_t__ msg_control; } ;
struct nn_cmsghdr {int /*<<< orphan*/  cmsg_len; } ;

/* Variables and functions */
 size_t NN_CMSG_ALIGN_ (int /*<<< orphan*/ ) ; 
 size_t NN_CMSG_SPACE (int /*<<< orphan*/ ) ; 
 size_t NN_MSG ; 
 size_t nn_chunk_size (char*) ; 
 scalar_t__ nn_slow (int) ; 

struct nn_cmsghdr *nn_cmsg_nxthdr_ (const struct nn_msghdr *mhdr,
    const struct nn_cmsghdr *cmsg)
{
    char *data;
    size_t sz;
    struct nn_cmsghdr *next;
    size_t headsz;

    /*  Early return if no message is provided. */
    if (nn_slow (mhdr == NULL))
        return NULL;

    /*  Get the actual data. */
    if (mhdr->msg_controllen == NN_MSG) {
        data = *((void**) mhdr->msg_control);
        sz = nn_chunk_size (data);
    }
    else {
        data = (char*) mhdr->msg_control;
        sz = mhdr->msg_controllen;
    }

    /*  Ancillary data allocation was not even large enough for one element. */
    if (nn_slow (sz < NN_CMSG_SPACE (0)))
        return NULL;

    /*  If cmsg is set to NULL we are going to return first property.
        Otherwise move to the next property. */
    if (!cmsg)
        next = (struct nn_cmsghdr*) data;
    else
        next = (struct nn_cmsghdr*)
            (((char*) cmsg) + NN_CMSG_ALIGN_ (cmsg->cmsg_len));

    /*  If there's no space for next property, treat it as the end
        of the property list. */
    headsz = ((char*) next) - data;
    if (headsz + NN_CMSG_SPACE (0) > sz ||
          headsz + NN_CMSG_ALIGN_ (next->cmsg_len) > sz)
        return NULL;

    /*  Success. */
    return next;
}