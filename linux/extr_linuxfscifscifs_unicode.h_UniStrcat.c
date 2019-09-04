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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */

__attribute__((used)) static inline __le16 *
UniStrcat(__le16 *ucs1, const __le16 *ucs2)
{
	__le16 *anchor = ucs1;	/* save a pointer to start of ucs1 */

	while (*ucs1++) ;	/* To end of first string */
	ucs1--;			/* Return to the null */
	while ((*ucs1++ = *ucs2++)) ;	/* copy string 2 over */
	return anchor;
}