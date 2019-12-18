#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double contentSize; int /*<<< orphan*/  contentChecksumFlag; int /*<<< orphan*/  blockMode; int /*<<< orphan*/  blockSizeID; int /*<<< orphan*/  blockChecksumFlag; } ;
struct TYPE_6__ {size_t frameType; TYPE_5__ lz4FrameInfo; } ;
struct TYPE_7__ {scalar_t__ frameCount; TYPE_1__ frameSummary; int /*<<< orphan*/  allContentSize; int /*<<< orphan*/  eqBlockTypes; int /*<<< orphan*/  eqFrameTypes; int /*<<< orphan*/  fileSize; } ;
typedef  scalar_t__ LZ4IO_infoResult ;
typedef  TYPE_1__ LZ4IO_frameInfo_t ;
typedef  TYPE_2__ LZ4IO_cFileInfo_t ;
typedef  int /*<<< orphan*/  LZ4F_dctx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int /*<<< orphan*/  EXM_THROW (int,char*,...) ; 
#define  LEGACY_MAGICNUMBER 130 
 int LZ4F_HEADER_SIZE_MAX ; 
 int /*<<< orphan*/  LZ4F_HEADER_SIZE_MIN ; 
 int /*<<< orphan*/  LZ4F_VERSION ; 
 size_t LZ4F_createDecompressionContext (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LZ4F_freeDecompressionContext (int /*<<< orphan*/ *) ; 
 size_t LZ4F_getFrameInfo (int /*<<< orphan*/ *,TYPE_5__*,unsigned char*,size_t*) ; 
 size_t LZ4F_headerSize (unsigned char**,int /*<<< orphan*/ ) ; 
 unsigned int LZ4F_isError (size_t) ; 
 TYPE_1__ LZ4IO_INIT_FRAMEINFO ; 
 scalar_t__ LZ4IO_LZ4F_OK ; 
#define  LZ4IO_MAGICNUMBER 129 
#define  LZ4IO_SKIPPABLE0 128 
 int /*<<< orphan*/  LZ4IO_blockTypeID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ LZ4IO_format_not_known ; 
 int /*<<< orphan*/ * LZ4IO_frameTypeNames ; 
 scalar_t__ LZ4IO_isSkippableMagicNumber (unsigned int) ; 
 int /*<<< orphan*/ * LZ4IO_openSrcFile (char const*) ; 
 void* LZ4IO_readLE32 (unsigned char*) ; 
 unsigned long long LZ4IO_skipBlocksData (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long LZ4IO_skipLegacyBlocksData (int /*<<< orphan*/ * const) ; 
 size_t MAGICNUMBER_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  UTIL_getFileSize (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ * const) ; 
 void* fread (unsigned char*,int,int,int /*<<< orphan*/ * const) ; 
 int fseek_u32 (int /*<<< orphan*/ * const,unsigned int const,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ * const) ; 
 size_t legacyFrame ; 
 size_t lz4Frame ; 
 size_t skippableFrame ; 

__attribute__((used)) static LZ4IO_infoResult
LZ4IO_getCompressedFileInfo(LZ4IO_cFileInfo_t* cfinfo, const char* input_filename)
{
    LZ4IO_infoResult result = LZ4IO_format_not_known;  /* default result (error) */
    unsigned char buffer[LZ4F_HEADER_SIZE_MAX];
    FILE* const finput = LZ4IO_openSrcFile(input_filename);
    cfinfo->fileSize = UTIL_getFileSize(input_filename);

    while (!feof(finput)) {
        LZ4IO_frameInfo_t frameInfo = LZ4IO_INIT_FRAMEINFO;
        unsigned magicNumber;
        /* Get MagicNumber */
        size_t nbReadBytes = fread(buffer, 1, MAGICNUMBER_SIZE, finput);
        if (nbReadBytes == 0) { break; } /* EOF */
        result = LZ4IO_format_not_known;  /* default result (error) */
        if (nbReadBytes != MAGICNUMBER_SIZE)
            EXM_THROW(40, "Unrecognized header : Magic Number unreadable");
        magicNumber = LZ4IO_readLE32(buffer);   /* Little Endian format */
        if (LZ4IO_isSkippableMagicNumber(magicNumber))
            magicNumber = LZ4IO_SKIPPABLE0;   /* fold skippable magic numbers */

        switch (magicNumber) {
        case LZ4IO_MAGICNUMBER:
            if (cfinfo->frameSummary.frameType != lz4Frame) cfinfo->eqFrameTypes = 0;
            /* Get frame info */
            {   const size_t readBytes = fread(buffer + MAGICNUMBER_SIZE, 1, LZ4F_HEADER_SIZE_MIN - MAGICNUMBER_SIZE, finput);
                if (!readBytes || ferror(finput)) EXM_THROW(71, "Error reading %s", input_filename);
            }
            {   size_t hSize = LZ4F_headerSize(&buffer, LZ4F_HEADER_SIZE_MIN);
                if (!LZ4F_isError(hSize)) {
                    if (hSize > (LZ4F_HEADER_SIZE_MIN + MAGICNUMBER_SIZE)) {
                        /* We've already read LZ4F_HEADER_SIZE_MIN so read any extra until hSize*/
                        const size_t readBytes = fread(buffer + LZ4F_HEADER_SIZE_MIN, 1, hSize - LZ4F_HEADER_SIZE_MIN, finput);
                        if (!readBytes || ferror(finput)) EXM_THROW(72, "Error reading %s", input_filename);
                    }
                    /* Create decompression context */
                    {   LZ4F_dctx* dctx;
                        unsigned isError = LZ4F_isError(LZ4F_createDecompressionContext(&dctx, LZ4F_VERSION));
                        if (!isError) {
                            isError = LZ4F_isError(LZ4F_getFrameInfo(dctx, &frameInfo.lz4FrameInfo, buffer, &hSize));
                            LZ4F_freeDecompressionContext(dctx);
                            if (!isError) {
                                if ((cfinfo->frameSummary.lz4FrameInfo.blockSizeID != frameInfo.lz4FrameInfo.blockSizeID ||
                                        cfinfo->frameSummary.lz4FrameInfo.blockMode != frameInfo.lz4FrameInfo.blockMode)
                                        && cfinfo->frameCount != 0)
                                    cfinfo->eqBlockTypes = 0;
                                {   const unsigned long long totalBlocksSize = LZ4IO_skipBlocksData(finput,
                                            frameInfo.lz4FrameInfo.blockChecksumFlag,
                                            frameInfo.lz4FrameInfo.contentChecksumFlag);
                                    if (totalBlocksSize) {
                                        char bTypeBuffer[5];
                                        LZ4IO_blockTypeID(frameInfo.lz4FrameInfo.blockSizeID, frameInfo.lz4FrameInfo.blockMode, bTypeBuffer);
                                        DISPLAYLEVEL(3, "    %6llu %14s %5s %8s",
                                                     cfinfo->frameCount + 1,
                                                     LZ4IO_frameTypeNames[frameInfo.frameType],
                                                     bTypeBuffer,
                                                     frameInfo.lz4FrameInfo.contentChecksumFlag ? "XXH32" : "-");
                                        if (frameInfo.lz4FrameInfo.contentSize) {
                                            {   double const ratio = (double)(totalBlocksSize + hSize) / frameInfo.lz4FrameInfo.contentSize * 100;
                                                DISPLAYLEVEL(3, " %20llu %20llu %9.2f%%\n",
                                                             totalBlocksSize + hSize,
                                                             frameInfo.lz4FrameInfo.contentSize,
                                                             ratio);
                                            }
                                            /* Now we've consumed frameInfo we can use it to store the total contentSize */
                                            frameInfo.lz4FrameInfo.contentSize += cfinfo->frameSummary.lz4FrameInfo.contentSize;
                                        }
                                        else {
                                            DISPLAYLEVEL(3, " %20llu %20s %9s \n", totalBlocksSize + hSize, "-", "-");
                                            cfinfo->allContentSize = 0;
                                        }
                                        result = LZ4IO_LZ4F_OK;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        case LEGACY_MAGICNUMBER:
            frameInfo.frameType = legacyFrame;
            if (cfinfo->frameSummary.frameType != legacyFrame && cfinfo->frameCount != 0) cfinfo->eqFrameTypes = 0;
            cfinfo->eqBlockTypes = 0;
            cfinfo->allContentSize = 0;
            {   const unsigned long long totalBlocksSize = LZ4IO_skipLegacyBlocksData(finput);
                if (totalBlocksSize) {
                    DISPLAYLEVEL(3, "    %6llu %14s %5s %8s %20llu %20s %9s\n",
                                 cfinfo->frameCount + 1,
                                 LZ4IO_frameTypeNames[frameInfo.frameType],
                                 "-", "-",
                                 totalBlocksSize + 4,
                                 "-", "-");
                    result = LZ4IO_LZ4F_OK;
                }
            }
            break;
        case LZ4IO_SKIPPABLE0:
            frameInfo.frameType = skippableFrame;
            if (cfinfo->frameSummary.frameType != skippableFrame && cfinfo->frameCount != 0) cfinfo->eqFrameTypes = 0;
            cfinfo->eqBlockTypes = 0;
            cfinfo->allContentSize = 0;
            {   nbReadBytes = fread(buffer, 1, 4, finput);
                if (nbReadBytes != 4)
                    EXM_THROW(42, "Stream error : skippable size unreadable");
            }
            {   unsigned const size = LZ4IO_readLE32(buffer);
                int const errorNb = fseek_u32(finput, size, SEEK_CUR);
                if (errorNb != 0)
                    EXM_THROW(43, "Stream error : cannot skip skippable area");
                DISPLAYLEVEL(3, "    %6llu %14s %5s %8s %20u %20s %9s\n",
                             cfinfo->frameCount + 1,
                             "SkippableFrame",
                             "-", "-", size + 8, "-", "-");

                result = LZ4IO_LZ4F_OK;
            }
            break;
        default:
            {   long int const position = ftell(finput);  /* only works for files < 2 GB */
                DISPLAYLEVEL(3, "Stream followed by undecodable data ");
                if (position != -1L)
                    DISPLAYLEVEL(3, "at position %i ", (int)position);
                DISPLAYLEVEL(3, "\n");
            }
        break;
        }
        if (result != LZ4IO_LZ4F_OK) {
            break;
        }
        cfinfo->frameSummary = frameInfo;
        cfinfo->frameCount++;
    }
    fclose(finput);
    return result;
}