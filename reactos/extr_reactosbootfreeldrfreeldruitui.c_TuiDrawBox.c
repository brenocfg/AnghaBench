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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
typedef  char UCHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 char D_LL ; 
 char D_LR ; 
 char D_UL ; 
 char D_UR ; 
 char HD_LL ; 
 char HD_LR ; 
 char HD_UL ; 
 char HD_UR ; 
 char HORZ ; 
 char LL ; 
 char LR ; 
 int /*<<< orphan*/  TuiDrawShadow (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TuiFillArea (scalar_t__,scalar_t__,scalar_t__,scalar_t__,char,char) ; 
 char UL ; 
 char UR ; 
 char VD_LL ; 
 char VD_LR ; 
 char VD_UL ; 
 char VD_UR ; 
 char VERT ; 

VOID TuiDrawBox(ULONG Left, ULONG Top, ULONG Right, ULONG Bottom, UCHAR VertStyle, UCHAR HorzStyle, BOOLEAN Fill, BOOLEAN Shadow, UCHAR Attr)
{
    UCHAR    ULCorner, URCorner, LLCorner, LRCorner;

    // Calculate the corner values
    if (HorzStyle == HORZ)
    {
        if (VertStyle == VERT)
        {
            ULCorner = UL;
            URCorner = UR;
            LLCorner = LL;
            LRCorner = LR;
        }
        else // VertStyle == D_VERT
        {
            ULCorner = VD_UL;
            URCorner = VD_UR;
            LLCorner = VD_LL;
            LRCorner = VD_LR;
        }
    }
    else // HorzStyle == D_HORZ
    {
        if (VertStyle == VERT)
        {
            ULCorner = HD_UL;
            URCorner = HD_UR;
            LLCorner = HD_LL;
            LRCorner = HD_LR;
        }
        else // VertStyle == D_VERT
        {
            ULCorner = D_UL;
            URCorner = D_UR;
            LLCorner = D_LL;
            LRCorner = D_LR;
        }
    }

    // Fill in box background
    if (Fill)
    {
        TuiFillArea(Left, Top, Right, Bottom, ' ', Attr);
    }

    // Fill in corners
    TuiFillArea(Left, Top, Left, Top, ULCorner, Attr);
    TuiFillArea(Right, Top, Right, Top, URCorner, Attr);
    TuiFillArea(Left, Bottom, Left, Bottom, LLCorner, Attr);
    TuiFillArea(Right, Bottom, Right, Bottom, LRCorner, Attr);

    // Fill in left line
    TuiFillArea(Left, Top+1, Left, Bottom-1, VertStyle, Attr);
    // Fill in top line
    TuiFillArea(Left+1, Top, Right-1, Top, HorzStyle, Attr);
    // Fill in right line
    TuiFillArea(Right, Top+1, Right, Bottom-1, VertStyle, Attr);
    // Fill in bottom line
    TuiFillArea(Left+1, Bottom, Right-1, Bottom, HorzStyle, Attr);

    // Draw the shadow
    if (Shadow)
    {
        TuiDrawShadow(Left, Top, Right, Bottom);
    }
}