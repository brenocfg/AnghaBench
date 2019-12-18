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
typedef  int /*<<< orphan*/  LZ4F_preferences_t ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (char* const) ; 
 int /*<<< orphan*/  FUZZ_ASSERT_MSG (int,char*) ; 
 int /*<<< orphan*/ * FUZZ_dataProducer_create (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  FUZZ_dataProducer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUZZ_dataProducer_preferences (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_remainingBytes (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_retrieve32 (int /*<<< orphan*/ *) ; 
 size_t FUZZ_decompressFrame (char* const,size_t,char* const,size_t const) ; 
 size_t FUZZ_getRange_from_uint32 (size_t const,int /*<<< orphan*/ ,size_t const) ; 
 size_t LZ4F_compressFrame (char* const,size_t const,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 
 size_t LZ4F_compressFrameBound (size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LZ4F_isError (size_t const) ; 
 int /*<<< orphan*/  free (char* const) ; 
 scalar_t__ malloc (size_t const) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char* const,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FUZZ_dataProducer_t *producer = FUZZ_dataProducer_create(data, size);
    LZ4F_preferences_t const prefs = FUZZ_dataProducer_preferences(producer);
    size_t const dstCapacitySeed = FUZZ_dataProducer_retrieve32(producer);
    size = FUZZ_dataProducer_remainingBytes(producer);

    size_t const compressBound = LZ4F_compressFrameBound(size, &prefs);
    size_t const dstCapacity = FUZZ_getRange_from_uint32(dstCapacitySeed, 0, compressBound);

    char* const dst = (char*)malloc(dstCapacity);
    char* const rt = (char*)malloc(size);

    FUZZ_ASSERT(dst);
    FUZZ_ASSERT(rt);

    /* If compression succeeds it must round trip correctly. */
    size_t const dstSize =
            LZ4F_compressFrame(dst, dstCapacity, data, size, &prefs);
    if (!LZ4F_isError(dstSize)) {
        size_t const rtSize = FUZZ_decompressFrame(rt, size, dst, dstSize);
        FUZZ_ASSERT_MSG(rtSize == size, "Incorrect regenerated size");
        FUZZ_ASSERT_MSG(!memcmp(data, rt, size), "Corruption!");
    }

    free(dst);
    free(rt);
    FUZZ_dataProducer_free(producer);

    return 0;
}