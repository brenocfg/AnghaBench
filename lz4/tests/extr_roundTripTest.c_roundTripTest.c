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
typedef  int (* compressFn ) (char const*,char*,int,int,int const) ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_MSG (int,char*,...) ; 
 int const LZ4HC_CLEVEL_MIN ; 
 int LZ4_compress_HC (char const*,char*,int,int,int const) ; 
 int LZ4_compress_fast (char const*,char*,int,int,int const) ; 
 int LZ4_decompress_safe (char const*,char*,int const,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t checkBuffers (void const*,void*,size_t) ; 
 int select_clevel (void const*,size_t) ; 

__attribute__((used)) static void roundTripTest(void* resultBuff, size_t resultBuffCapacity,
                          void* compressedBuff, size_t compressedBuffCapacity,
                    const void* srcBuff, size_t srcSize,
                          int clevel)
{
    int const proposed_clevel = clevel ? clevel : select_clevel(srcBuff, srcSize);
    int const selected_clevel = proposed_clevel < 0 ? -proposed_clevel : proposed_clevel;   /* if level < 0, it becomes an accelearion value */
    compressFn compress = selected_clevel >= LZ4HC_CLEVEL_MIN ? LZ4_compress_HC : LZ4_compress_fast;
    int const cSize = compress((const char*)srcBuff, (char*)compressedBuff, (int)srcSize, (int)compressedBuffCapacity, selected_clevel);
    CONTROL_MSG(cSize == 0, "Compression error !");

    {   int const dSize = LZ4_decompress_safe((const char*)compressedBuff, (char*)resultBuff, cSize, (int)resultBuffCapacity);
        CONTROL_MSG(dSize < 0, "Decompression detected an error !");
        CONTROL_MSG(dSize != (int)srcSize, "Decompression corruption error : wrong decompressed size !");
    }

    /* check potential content corruption error */
    assert(resultBuffCapacity >= srcSize);
    {   size_t const errorPos = checkBuffers(srcBuff, resultBuff, srcSize);
        CONTROL_MSG(errorPos != srcSize,
                    "Silent decoding corruption, at pos %u !!!",
                    (unsigned)errorPos);
    }

}