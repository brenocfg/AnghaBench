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

/* Variables and functions */
 int QUANT_MASK ; 
 unsigned char SEG_SHIFT ; 
 int search (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seg_aend ; 

__attribute__((used)) static inline unsigned char
linear2alaw(int pcm_val)	/* 2's complement (16-bit range) */
    /* changed from "short" *drago* */
{
    int		mask;	/* changed from "short" *drago* */
    int		seg;	/* changed from "short" *drago* */
    unsigned char	aval;

    pcm_val = pcm_val >> 3;

    if (pcm_val >= 0) {
        mask = 0xD5;		/* sign (7th) bit = 1 */
    } else {
        mask = 0x55;		/* sign bit = 0 */
        pcm_val = -pcm_val - 1;
    }

    /* Convert the scaled magnitude to segment number. */
    seg = search(pcm_val, seg_aend, 8);

    /* Combine the sign, segment, and quantization bits. */

    if (seg >= 8)		/* out of range, return maximum value. */
        return (unsigned char) (0x7F ^ mask);
    else {
        aval = (unsigned char) seg << SEG_SHIFT;
        if (seg < 2)
            aval |= (pcm_val >> 1) & QUANT_MASK;
        else
            aval |= (pcm_val >> seg) & QUANT_MASK;
        return (aval ^ mask);
    }
}