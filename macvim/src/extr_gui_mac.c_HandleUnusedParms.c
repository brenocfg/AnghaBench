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
typedef  int /*<<< orphan*/  missedKeyword ;
typedef  int /*<<< orphan*/  Ptr ;
typedef  scalar_t__ OSErr ;
typedef  int /*<<< orphan*/  DescType ;
typedef  int /*<<< orphan*/  AppleEvent ;
typedef  int /*<<< orphan*/  AEKeyword ;

/* Variables and functions */
 scalar_t__ AEGetAttributePtr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,long*) ; 
 scalar_t__ errAEDescNotFound ; 
 scalar_t__ errAEEventNotHandled ; 
 int /*<<< orphan*/  keyMissedKeywordAttr ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  typeKeyword ; 

OSErr
HandleUnusedParms(const AppleEvent *theAEvent)
{
    OSErr	error;
    long	actualSize;
    DescType	dummyType;
    AEKeyword	missedKeyword;

    /* Get the "missed keyword" attribute from the AppleEvent. */
    error = AEGetAttributePtr(theAEvent, keyMissedKeywordAttr,
			      typeKeyword, &dummyType,
			      (Ptr)&missedKeyword, sizeof(missedKeyword),
			      &actualSize);

    /* If the descriptor isn't found, then we got the required parameters. */
    if (error == errAEDescNotFound)
    {
	error = noErr;
    }
    else
    {
#if 0
	/* Why is this removed? */
	error = errAEEventNotHandled;
#endif
    }

    return error;
}