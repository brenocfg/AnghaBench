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
typedef  int /*<<< orphan*/  PyObject ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/  FSSpec ;
typedef  int /*<<< orphan*/  FSRef ;
typedef  int /*<<< orphan*/  CFURLRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  ATSFontContainerRef ;

/* Variables and functions */
 scalar_t__ ATSFontActivateFromFileReference (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ATSFontActivateFromFileSpecification (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringCreateWithCString (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFURLCreateWithFileSystemPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CFURLGetFSRef (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FSGetCatalogInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  kATSFontContextLocal ; 
 int /*<<< orphan*/  kATSFontFormatUnspecified ; 
 int /*<<< orphan*/  kATSOptionFlagsDefault ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  kCFURLPOSIXPathStyle ; 
 int /*<<< orphan*/  kFSCatInfoNone ; 
 scalar_t__ noErr ; 

__attribute__((used)) static PyObject* loadfont(PyObject* self, PyObject* args) {
  PyObject*   result = Py_False;
  const char* path = NULL;
  int         ok = PyArg_ParseTuple(args, "s", &path);

  if (ok) {
    CFStringRef componentPath = CFStringCreateWithCString(kCFAllocatorDefault,
        path, kCFStringEncodingUTF8);
    CFURLRef componentURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
        componentPath, kCFURLPOSIXPathStyle, false);
    FSRef fsref;

    if (CFURLGetFSRef(componentURL, &fsref)) {
      OSStatus err = noErr;
      ATSFontContainerRef fontContainerRef;  // we don't deactivate the font
#if (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_4)
      err = ATSFontActivateFromFileReference(&fsref,
          kATSFontContextLocal, kATSFontFormatUnspecified, NULL,
          kATSOptionFlagsDefault, &fontContainerRef);
#else
      FSSpec fsSpec;
      FSRef  fsRef;
      if ((err = FSGetCatalogInfo(
              &fsRef, kFSCatInfoNone, NULL, NULL, &fsSpec, NULL)) == noErr) {
        err = ATSFontActivateFromFileSpecification(&fsSpec,
            kATSFontContextLocal, kATSFontFormatUnspecified, NULL,
            kATSOptionFlagsDefault, &fontContainerRef);
      }

#endif

      if (err == noErr) {
        result = Py_True;
      }
    }
    CFRelease(componentURL);
    CFRelease(componentPath);       
  }
  return result;
}