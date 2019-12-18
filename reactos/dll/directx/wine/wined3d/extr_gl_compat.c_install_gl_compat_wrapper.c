#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_glFogCoorddvEXT; int /*<<< orphan*/  p_glFogCoorddEXT; int /*<<< orphan*/  p_glFogCoordfvEXT; int /*<<< orphan*/  p_glFogCoordfEXT; int /*<<< orphan*/  p_glMultiTexCoord4svARB; int /*<<< orphan*/  p_glMultiTexCoord2svARB; int /*<<< orphan*/  p_glMultiTexCoord4fvARB; int /*<<< orphan*/  p_glMultiTexCoord4fARB; int /*<<< orphan*/  p_glMultiTexCoord3fvARB; int /*<<< orphan*/  p_glMultiTexCoord3fARB; int /*<<< orphan*/  p_glMultiTexCoord2fvARB; int /*<<< orphan*/  p_glMultiTexCoord2fARB; int /*<<< orphan*/  p_glMultiTexCoord1fvARB; int /*<<< orphan*/  p_glMultiTexCoord1fARB; int /*<<< orphan*/  p_glClientActiveTextureARB; int /*<<< orphan*/  p_glActiveTexture; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_glColor4ub; int /*<<< orphan*/  p_glColor3fv; int /*<<< orphan*/  p_glColor3f; int /*<<< orphan*/  p_glColor4fv; int /*<<< orphan*/  p_glColor4f; int /*<<< orphan*/  p_glVertex3fv; int /*<<< orphan*/  p_glVertex3f; int /*<<< orphan*/  p_glVertex4fv; int /*<<< orphan*/  p_glVertex4f; int /*<<< orphan*/  p_glFogfv; int /*<<< orphan*/  p_glFogf; int /*<<< orphan*/  p_glFogiv; int /*<<< orphan*/  p_glFogi; int /*<<< orphan*/  p_glGetDoublev; int /*<<< orphan*/  p_glGetFloatv; int /*<<< orphan*/  p_glGetIntegerv; } ;
struct TYPE_5__ {TYPE_3__ ext; TYPE_1__ gl; } ;
struct wined3d_gl_info {void** supported; TYPE_2__ gl_ops; } ;
typedef  enum wined3d_gl_extension { ____Placeholder_wined3d_gl_extension } wined3d_gl_extension ;

/* Variables and functions */
 size_t ARB_FRAGMENT_PROGRAM ; 
 size_t ARB_FRAGMENT_SHADER ; 
#define  ARB_MULTITEXTURE 129 
#define  EXT_FOG_COORD 128 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  glDisableWINE ; 
 int /*<<< orphan*/  glEnableWINE ; 
 int /*<<< orphan*/  old_fogcoord_glColor4f ; 
 int /*<<< orphan*/  old_fogcoord_glDisable ; 
 int /*<<< orphan*/  old_fogcoord_glEnable ; 
 int /*<<< orphan*/  old_fogcoord_glFogf ; 
 int /*<<< orphan*/  old_fogcoord_glFogfv ; 
 int /*<<< orphan*/  old_fogcoord_glFogi ; 
 int /*<<< orphan*/  old_fogcoord_glFogiv ; 
 int /*<<< orphan*/  old_fogcoord_glVertex4f ; 
 int /*<<< orphan*/  old_multitex_glGetDoublev ; 
 int /*<<< orphan*/  old_multitex_glGetFloatv ; 
 int /*<<< orphan*/  old_multitex_glGetIntegerv ; 
 int /*<<< orphan*/  wine_glActiveTexture ; 
 int /*<<< orphan*/  wine_glClientActiveTextureARB ; 
 int /*<<< orphan*/  wine_glColor3f ; 
 int /*<<< orphan*/  wine_glColor3fv ; 
 int /*<<< orphan*/  wine_glColor4f ; 
 int /*<<< orphan*/  wine_glColor4fv ; 
 int /*<<< orphan*/  wine_glColor4ub ; 
 int /*<<< orphan*/  wine_glDisable ; 
 int /*<<< orphan*/  wine_glEnable ; 
 int /*<<< orphan*/  wine_glFogCoorddEXT ; 
 int /*<<< orphan*/  wine_glFogCoorddvEXT ; 
 int /*<<< orphan*/  wine_glFogCoordfEXT ; 
 int /*<<< orphan*/  wine_glFogCoordfvEXT ; 
 int /*<<< orphan*/  wine_glFogf ; 
 int /*<<< orphan*/  wine_glFogfv ; 
 int /*<<< orphan*/  wine_glFogi ; 
 int /*<<< orphan*/  wine_glFogiv ; 
 int /*<<< orphan*/  wine_glGetDoublev ; 
 int /*<<< orphan*/  wine_glGetFloatv ; 
 int /*<<< orphan*/  wine_glGetIntegerv ; 
 int /*<<< orphan*/  wine_glMultiTexCoord1fARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord1fvARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord2fARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord2fvARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord2svARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord3fARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord3fvARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord4fARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord4fvARB ; 
 int /*<<< orphan*/  wine_glMultiTexCoord4svARB ; 
 int /*<<< orphan*/  wine_glVertex3f ; 
 int /*<<< orphan*/  wine_glVertex3fv ; 
 int /*<<< orphan*/  wine_glVertex4f ; 
 int /*<<< orphan*/  wine_glVertex4fv ; 

void install_gl_compat_wrapper(struct wined3d_gl_info *gl_info, enum wined3d_gl_extension ext)
{
    switch (ext)
    {
        case ARB_MULTITEXTURE:
            if (gl_info->supported[ARB_MULTITEXTURE])
                return;
            if (gl_info->gl_ops.ext.p_glActiveTexture == wine_glActiveTexture)
            {
                FIXME("ARB_multitexture emulation hooks already applied.\n");
                return;
            }
            TRACE("Applying GL_ARB_multitexture emulation hooks.\n");
            gl_info->gl_ops.ext.p_glActiveTexture           = wine_glActiveTexture;
            gl_info->gl_ops.ext.p_glClientActiveTextureARB  = wine_glClientActiveTextureARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord1fARB      = wine_glMultiTexCoord1fARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord1fvARB     = wine_glMultiTexCoord1fvARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord2fARB      = wine_glMultiTexCoord2fARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord2fvARB     = wine_glMultiTexCoord2fvARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord3fARB      = wine_glMultiTexCoord3fARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord3fvARB     = wine_glMultiTexCoord3fvARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord4fARB      = wine_glMultiTexCoord4fARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord4fvARB     = wine_glMultiTexCoord4fvARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord2svARB     = wine_glMultiTexCoord2svARB;
            gl_info->gl_ops.ext.p_glMultiTexCoord4svARB     = wine_glMultiTexCoord4svARB;
            old_multitex_glGetIntegerv = gl_info->gl_ops.gl.p_glGetIntegerv;
            gl_info->gl_ops.gl.p_glGetIntegerv = wine_glGetIntegerv;
            old_multitex_glGetFloatv = gl_info->gl_ops.gl.p_glGetFloatv;
            gl_info->gl_ops.gl.p_glGetFloatv = wine_glGetFloatv;
            old_multitex_glGetDoublev = gl_info->gl_ops.gl.p_glGetDoublev;
            gl_info->gl_ops.gl.p_glGetDoublev = wine_glGetDoublev;
            gl_info->supported[ARB_MULTITEXTURE] = TRUE;
            return;

        case EXT_FOG_COORD:
            /* This emulation isn't perfect. There are a number of potential problems, but they should
             * not matter in practise:
             *
             * Fog vs fragment shader: If we are using GL_ARB_fragment_program with the fog option, the
             * glDisable(GL_FOG) here won't matter. However, if we have GL_ARB_fragment_program, it is pretty
             * unlikely that we don't have GL_EXT_fog_coord. Besides, we probably have GL_ARB_vertex_program
             * too, which would allow fog coord emulation in a fixed function vertex pipeline replacement.
             *
             * Fog vs texture: We apply the fog in the vertex color. An app could set up texturing settings which
             * ignore the vertex color, thus effectively disabling our fog. However, in D3D this type of fog is
             * a per-vertex fog too, so the apps shouldn't do that.
             *
             * Fog vs lighting: The app could in theory use D3DFOG_NONE table and D3DFOG_NONE vertex fog with
             * untransformed vertices. That enables lighting and fog coords at the same time, and the lighting
             * calculations could affect the already blended in fog color. There's nothing we can do against that,
             * but most apps using fog color do their own lighting too and often even use RHW vertices. So live
             * with it.
             */
            if (gl_info->supported[EXT_FOG_COORD])
                return;
            if (gl_info->gl_ops.gl.p_glFogi == wine_glFogi)
            {
                FIXME("EXT_fog_coord emulation hooks already applied.\n");
                return;
            }
            TRACE("Applying GL_ARB_fog_coord emulation hooks\n");

            /* This probably means that the implementation doesn't advertise the extension, but implicitly supports
             * it via the GL core version, or someone messed around in the extension table in directx.c. Add version-
             * dependent loading for this extension if we ever hit this situation
             */
            if (gl_info->supported[ARB_FRAGMENT_PROGRAM])
            {
                FIXME("GL implementation supports GL_ARB_fragment_program but not GL_EXT_fog_coord\n");
                FIXME("The fog coord emulation will most likely fail\n");
            }
            else if (gl_info->supported[ARB_FRAGMENT_SHADER])
            {
                FIXME("GL implementation supports GL_ARB_fragment_shader but not GL_EXT_fog_coord\n");
                FIXME("The fog coord emulation will most likely fail\n");
            }

            old_fogcoord_glFogi = gl_info->gl_ops.gl.p_glFogi;
            gl_info->gl_ops.gl.p_glFogi = wine_glFogi;
            old_fogcoord_glFogiv = gl_info->gl_ops.gl.p_glFogiv;
            gl_info->gl_ops.gl.p_glFogiv = wine_glFogiv;
            old_fogcoord_glFogf = gl_info->gl_ops.gl.p_glFogf;
            gl_info->gl_ops.gl.p_glFogf = wine_glFogf;
            old_fogcoord_glFogfv = gl_info->gl_ops.gl.p_glFogfv;
            gl_info->gl_ops.gl.p_glFogfv = wine_glFogfv;
            old_fogcoord_glEnable = glEnableWINE;
            glEnableWINE = wine_glEnable;
            old_fogcoord_glDisable = glDisableWINE;
            glDisableWINE = wine_glDisable;

            old_fogcoord_glVertex4f = gl_info->gl_ops.gl.p_glVertex4f;
            gl_info->gl_ops.gl.p_glVertex4f = wine_glVertex4f;
            gl_info->gl_ops.gl.p_glVertex4fv = wine_glVertex4fv;
            gl_info->gl_ops.gl.p_glVertex3f = wine_glVertex3f;
            gl_info->gl_ops.gl.p_glVertex3fv = wine_glVertex3fv;

            old_fogcoord_glColor4f = gl_info->gl_ops.gl.p_glColor4f;
            gl_info->gl_ops.gl.p_glColor4f = wine_glColor4f;
            gl_info->gl_ops.gl.p_glColor4fv = wine_glColor4fv;
            gl_info->gl_ops.gl.p_glColor3f = wine_glColor3f;
            gl_info->gl_ops.gl.p_glColor3fv = wine_glColor3fv;
            gl_info->gl_ops.gl.p_glColor4ub = wine_glColor4ub;

            gl_info->gl_ops.ext.p_glFogCoordfEXT = wine_glFogCoordfEXT;
            gl_info->gl_ops.ext.p_glFogCoordfvEXT = wine_glFogCoordfvEXT;
            gl_info->gl_ops.ext.p_glFogCoorddEXT = wine_glFogCoorddEXT;
            gl_info->gl_ops.ext.p_glFogCoorddvEXT = wine_glFogCoorddvEXT;
            gl_info->supported[EXT_FOG_COORD] = TRUE;
            return;

        default:
            FIXME("Extension %u emulation not supported.\n", ext);
    }
}