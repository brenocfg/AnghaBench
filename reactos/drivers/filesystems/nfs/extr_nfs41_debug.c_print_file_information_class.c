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
#define  FileAllInformation 153 
#define  FileAllocationInformation 152 
#define  FileAttributeTagInformation 151 
#define  FileBasicInformation 150 
#define  FileBothDirectoryInformation 149 
#define  FileCompressionInformation 148 
#define  FileDirectoryInformation 147 
#define  FileDispositionInformation 146 
#define  FileEaInformation 145 
#define  FileEndOfFileInformation 144 
#define  FileFullDirectoryInformation 143 
#define  FileIdBothDirectoryInformation 142 
#define  FileIdFullDirectoryInformation 141 
#define  FileInternalInformation 140 
#define  FileLinkInformation 139 
#define  FileNameInformation 138 
#define  FileNamesInformation 137 
#define  FileNetworkOpenInformation 136 
#define  FileObjectIdInformation 135 
#define  FilePositionInformation 134 
#define  FileQuotaInformation 133 
#define  FileRenameInformation 132 
#define  FileReparsePointInformation 131 
#define  FileStandardInformation 130 
#define  FileStreamInformation 129 
#define  FileValidDataLengthInformation 128 

unsigned char * print_file_information_class(int InfoClass) 
{
    switch(InfoClass) {
        case FileBothDirectoryInformation:
            return (unsigned char *)"FileBothDirectoryInformation";
        case FileDirectoryInformation:
            return (unsigned char *)"FileDirectoryInformation";
        case FileFullDirectoryInformation:
            return (unsigned char *)"FileFullDirectoryInformation";
        case FileIdBothDirectoryInformation:
            return (unsigned char *)"FileIdBothDirectoryInformation";
        case FileIdFullDirectoryInformation:
            return (unsigned char *)"FileIdFullDirectoryInformation";
        case FileNamesInformation:
            return (unsigned char *)"FileNamesInformation";
        case FileObjectIdInformation:
            return (unsigned char *)"FileObjectIdInformation";
        case FileQuotaInformation:
            return (unsigned char *)"FileQuotaInformation";
        case FileReparsePointInformation:
            return (unsigned char *)"FileReparsePointInformation";
        case FileAllInformation:
            return (unsigned char *)"FileAllInformation";
        case FileAttributeTagInformation:
            return (unsigned char *)"FileAttributeTagInformation";
        case FileBasicInformation:
            return (unsigned char *)"FileBasicInformation";
        case FileCompressionInformation:
            return (unsigned char *)"FileCompressionInformation";
        case FileEaInformation:
            return (unsigned char *)"FileEaInformation";
        case FileInternalInformation:
            return (unsigned char *)"FileInternalInformation";
        case FileNameInformation:
            return (unsigned char *)"FileNameInformation";
        case FileNetworkOpenInformation:
            return (unsigned char *)"FileNetworkOpenInformation";
        case FilePositionInformation:
            return (unsigned char *)"FilePositionInformation";
        case FileStandardInformation:
            return (unsigned char *)"FileStandardInformation";
        case FileStreamInformation:
            return (unsigned char *)"FileStreamInformation";
        case FileAllocationInformation:
            return (unsigned char *)"FileAllocationInformation";
        case FileDispositionInformation:
            return (unsigned char *)"FileDispositionInformation";
        case FileEndOfFileInformation:
            return (unsigned char *)"FileEndOfFileInformation";
        case FileLinkInformation:
            return (unsigned char *)"FileLinkInformation";
        case FileRenameInformation:
            return (unsigned char *)"FileRenameInformation";
        case FileValidDataLengthInformation:
            return (unsigned char *)"FileValidDataLengthInformation";
        default:
            return (unsigned char *)"UNKNOWN";
    }
}