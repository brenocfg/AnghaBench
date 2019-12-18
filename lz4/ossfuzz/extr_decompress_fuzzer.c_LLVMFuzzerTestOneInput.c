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
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (char* const) ; 
 int /*<<< orphan*/ * FUZZ_dataProducer_create (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  FUZZ_dataProducer_free (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_remainingBytes (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_retrieve32 (int /*<<< orphan*/ *) ; 
 size_t FUZZ_getRange_from_uint32 (size_t const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LZ4_decompress_safe_partial (char const*,char* const,size_t,size_t const,size_t const) ; 
 int /*<<< orphan*/  LZ4_decompress_safe_usingDict (char const*,char* const,size_t,size_t const,char* const,size_t const) ; 
 size_t MAX (size_t const,size_t const) ; 
 int /*<<< orphan*/  free (char* const) ; 
 scalar_t__ malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (char* const,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (char* const,int /*<<< orphan*/ ,size_t const) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FUZZ_dataProducer_t *producer = FUZZ_dataProducer_create(data, size);
    size_t const dstCapacitySeed = FUZZ_dataProducer_retrieve32(producer);
    size = FUZZ_dataProducer_remainingBytes(producer);

    size_t const dstCapacity = FUZZ_getRange_from_uint32(dstCapacitySeed, 0, 4 * size);
    size_t const smallDictSize = size + 1;
    size_t const largeDictSize = 64 * 1024 - 1;
    size_t const dictSize = MAX(smallDictSize, largeDictSize);
    char* const dst = (char*)malloc(dstCapacity);
    char* const dict = (char*)malloc(dictSize + size);
    char* const largeDict = dict;
    char* const dataAfterDict = dict + dictSize;
    char* const smallDict = dataAfterDict - smallDictSize;

    FUZZ_ASSERT(dst);
    FUZZ_ASSERT(dict);

    /* Prepare the dictionary. The data doesn't matter for decompression. */
    memset(dict, 0, dictSize);
    memcpy(dataAfterDict, data, size);

    /* Decompress using each possible dictionary configuration. */
    /* No dictionary. */
    LZ4_decompress_safe_usingDict((char const*)data, dst, size,
                                  dstCapacity, NULL, 0);
    /* Small external dictonary. */
    LZ4_decompress_safe_usingDict((char const*)data, dst, size,
                                  dstCapacity, smallDict, smallDictSize);
    /* Large external dictionary. */
    LZ4_decompress_safe_usingDict((char const*)data, dst, size,
                                  dstCapacity, largeDict, largeDictSize);
    /* Small prefix. */
    LZ4_decompress_safe_usingDict((char const*)dataAfterDict, dst, size,
                                  dstCapacity, smallDict, smallDictSize);
    /* Large prefix. */
    LZ4_decompress_safe_usingDict((char const*)data, dst, size,
                                  dstCapacity, largeDict, largeDictSize);
    /* Partial decompression. */
    LZ4_decompress_safe_partial((char const*)data, dst, size,
                                dstCapacity, dstCapacity);
    free(dst);
    free(dict);
    FUZZ_dataProducer_free(producer);

    return 0;
}