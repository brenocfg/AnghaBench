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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 size_t _find_emulation_prevention_byte (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static size_t _copy_to_rbsp(uint8_t* destData, size_t destSize, const uint8_t* sorcData, size_t sorcSize)
{
    size_t toCopy, totlSize = 0;

    for (;;) {
        if (destSize >= sorcSize) {
            return 0;
        }

        // The following line IS correct! We want to look in sorcData up to destSize bytes
        // We know destSize is smaller than sorcSize because of the previous line
        toCopy = _find_emulation_prevention_byte(sorcData, destSize);
        memcpy(destData, sorcData, toCopy);
        totlSize += toCopy;
        destData += toCopy;
        destSize -= toCopy;

        if (0 == destSize) {
            return totlSize;
        }

        // skip the emulation prevention byte
        totlSize += 1;
        sorcData += toCopy + 1;
        sorcSize -= toCopy + 1;
    }

    return 0;
}