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
typedef  scalar_t__ PFNGLVERTEXSTREAM4SVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM4SATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM4IVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM4IATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM4FVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM4FATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM4DVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM4DATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3SVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3SATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3IVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3IATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3FVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3FATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3DVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM3DATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2SVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2SATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2IVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2IATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2FVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2FATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2DVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM2DATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1SVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1SATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1IVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1IATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1FVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1FATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1DVATIPROC ;
typedef  scalar_t__ PFNGLVERTEXSTREAM1DATIPROC ;
typedef  scalar_t__ PFNGLVERTEXBLENDENVIATIPROC ;
typedef  scalar_t__ PFNGLVERTEXBLENDENVFATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3SVATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3SATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3IVATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3IATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3FVATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3FATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3DVATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3DATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3BVATIPROC ;
typedef  scalar_t__ PFNGLNORMALSTREAM3BATIPROC ;
typedef  scalar_t__ PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ATI_vertex_streams ; 
 scalar_t__ glad_glClientActiveVertexStreamATI ; 
 scalar_t__ glad_glNormalStream3bATI ; 
 scalar_t__ glad_glNormalStream3bvATI ; 
 scalar_t__ glad_glNormalStream3dATI ; 
 scalar_t__ glad_glNormalStream3dvATI ; 
 scalar_t__ glad_glNormalStream3fATI ; 
 scalar_t__ glad_glNormalStream3fvATI ; 
 scalar_t__ glad_glNormalStream3iATI ; 
 scalar_t__ glad_glNormalStream3ivATI ; 
 scalar_t__ glad_glNormalStream3sATI ; 
 scalar_t__ glad_glNormalStream3svATI ; 
 scalar_t__ glad_glVertexBlendEnvfATI ; 
 scalar_t__ glad_glVertexBlendEnviATI ; 
 scalar_t__ glad_glVertexStream1dATI ; 
 scalar_t__ glad_glVertexStream1dvATI ; 
 scalar_t__ glad_glVertexStream1fATI ; 
 scalar_t__ glad_glVertexStream1fvATI ; 
 scalar_t__ glad_glVertexStream1iATI ; 
 scalar_t__ glad_glVertexStream1ivATI ; 
 scalar_t__ glad_glVertexStream1sATI ; 
 scalar_t__ glad_glVertexStream1svATI ; 
 scalar_t__ glad_glVertexStream2dATI ; 
 scalar_t__ glad_glVertexStream2dvATI ; 
 scalar_t__ glad_glVertexStream2fATI ; 
 scalar_t__ glad_glVertexStream2fvATI ; 
 scalar_t__ glad_glVertexStream2iATI ; 
 scalar_t__ glad_glVertexStream2ivATI ; 
 scalar_t__ glad_glVertexStream2sATI ; 
 scalar_t__ glad_glVertexStream2svATI ; 
 scalar_t__ glad_glVertexStream3dATI ; 
 scalar_t__ glad_glVertexStream3dvATI ; 
 scalar_t__ glad_glVertexStream3fATI ; 
 scalar_t__ glad_glVertexStream3fvATI ; 
 scalar_t__ glad_glVertexStream3iATI ; 
 scalar_t__ glad_glVertexStream3ivATI ; 
 scalar_t__ glad_glVertexStream3sATI ; 
 scalar_t__ glad_glVertexStream3svATI ; 
 scalar_t__ glad_glVertexStream4dATI ; 
 scalar_t__ glad_glVertexStream4dvATI ; 
 scalar_t__ glad_glVertexStream4fATI ; 
 scalar_t__ glad_glVertexStream4fvATI ; 
 scalar_t__ glad_glVertexStream4iATI ; 
 scalar_t__ glad_glVertexStream4ivATI ; 
 scalar_t__ glad_glVertexStream4sATI ; 
 scalar_t__ glad_glVertexStream4svATI ; 

__attribute__((used)) static void load_GL_ATI_vertex_streams(GLADloadproc load) {
	if(!GLAD_GL_ATI_vertex_streams) return;
	glad_glVertexStream1sATI = (PFNGLVERTEXSTREAM1SATIPROC)load("glVertexStream1sATI");
	glad_glVertexStream1svATI = (PFNGLVERTEXSTREAM1SVATIPROC)load("glVertexStream1svATI");
	glad_glVertexStream1iATI = (PFNGLVERTEXSTREAM1IATIPROC)load("glVertexStream1iATI");
	glad_glVertexStream1ivATI = (PFNGLVERTEXSTREAM1IVATIPROC)load("glVertexStream1ivATI");
	glad_glVertexStream1fATI = (PFNGLVERTEXSTREAM1FATIPROC)load("glVertexStream1fATI");
	glad_glVertexStream1fvATI = (PFNGLVERTEXSTREAM1FVATIPROC)load("glVertexStream1fvATI");
	glad_glVertexStream1dATI = (PFNGLVERTEXSTREAM1DATIPROC)load("glVertexStream1dATI");
	glad_glVertexStream1dvATI = (PFNGLVERTEXSTREAM1DVATIPROC)load("glVertexStream1dvATI");
	glad_glVertexStream2sATI = (PFNGLVERTEXSTREAM2SATIPROC)load("glVertexStream2sATI");
	glad_glVertexStream2svATI = (PFNGLVERTEXSTREAM2SVATIPROC)load("glVertexStream2svATI");
	glad_glVertexStream2iATI = (PFNGLVERTEXSTREAM2IATIPROC)load("glVertexStream2iATI");
	glad_glVertexStream2ivATI = (PFNGLVERTEXSTREAM2IVATIPROC)load("glVertexStream2ivATI");
	glad_glVertexStream2fATI = (PFNGLVERTEXSTREAM2FATIPROC)load("glVertexStream2fATI");
	glad_glVertexStream2fvATI = (PFNGLVERTEXSTREAM2FVATIPROC)load("glVertexStream2fvATI");
	glad_glVertexStream2dATI = (PFNGLVERTEXSTREAM2DATIPROC)load("glVertexStream2dATI");
	glad_glVertexStream2dvATI = (PFNGLVERTEXSTREAM2DVATIPROC)load("glVertexStream2dvATI");
	glad_glVertexStream3sATI = (PFNGLVERTEXSTREAM3SATIPROC)load("glVertexStream3sATI");
	glad_glVertexStream3svATI = (PFNGLVERTEXSTREAM3SVATIPROC)load("glVertexStream3svATI");
	glad_glVertexStream3iATI = (PFNGLVERTEXSTREAM3IATIPROC)load("glVertexStream3iATI");
	glad_glVertexStream3ivATI = (PFNGLVERTEXSTREAM3IVATIPROC)load("glVertexStream3ivATI");
	glad_glVertexStream3fATI = (PFNGLVERTEXSTREAM3FATIPROC)load("glVertexStream3fATI");
	glad_glVertexStream3fvATI = (PFNGLVERTEXSTREAM3FVATIPROC)load("glVertexStream3fvATI");
	glad_glVertexStream3dATI = (PFNGLVERTEXSTREAM3DATIPROC)load("glVertexStream3dATI");
	glad_glVertexStream3dvATI = (PFNGLVERTEXSTREAM3DVATIPROC)load("glVertexStream3dvATI");
	glad_glVertexStream4sATI = (PFNGLVERTEXSTREAM4SATIPROC)load("glVertexStream4sATI");
	glad_glVertexStream4svATI = (PFNGLVERTEXSTREAM4SVATIPROC)load("glVertexStream4svATI");
	glad_glVertexStream4iATI = (PFNGLVERTEXSTREAM4IATIPROC)load("glVertexStream4iATI");
	glad_glVertexStream4ivATI = (PFNGLVERTEXSTREAM4IVATIPROC)load("glVertexStream4ivATI");
	glad_glVertexStream4fATI = (PFNGLVERTEXSTREAM4FATIPROC)load("glVertexStream4fATI");
	glad_glVertexStream4fvATI = (PFNGLVERTEXSTREAM4FVATIPROC)load("glVertexStream4fvATI");
	glad_glVertexStream4dATI = (PFNGLVERTEXSTREAM4DATIPROC)load("glVertexStream4dATI");
	glad_glVertexStream4dvATI = (PFNGLVERTEXSTREAM4DVATIPROC)load("glVertexStream4dvATI");
	glad_glNormalStream3bATI = (PFNGLNORMALSTREAM3BATIPROC)load("glNormalStream3bATI");
	glad_glNormalStream3bvATI = (PFNGLNORMALSTREAM3BVATIPROC)load("glNormalStream3bvATI");
	glad_glNormalStream3sATI = (PFNGLNORMALSTREAM3SATIPROC)load("glNormalStream3sATI");
	glad_glNormalStream3svATI = (PFNGLNORMALSTREAM3SVATIPROC)load("glNormalStream3svATI");
	glad_glNormalStream3iATI = (PFNGLNORMALSTREAM3IATIPROC)load("glNormalStream3iATI");
	glad_glNormalStream3ivATI = (PFNGLNORMALSTREAM3IVATIPROC)load("glNormalStream3ivATI");
	glad_glNormalStream3fATI = (PFNGLNORMALSTREAM3FATIPROC)load("glNormalStream3fATI");
	glad_glNormalStream3fvATI = (PFNGLNORMALSTREAM3FVATIPROC)load("glNormalStream3fvATI");
	glad_glNormalStream3dATI = (PFNGLNORMALSTREAM3DATIPROC)load("glNormalStream3dATI");
	glad_glNormalStream3dvATI = (PFNGLNORMALSTREAM3DVATIPROC)load("glNormalStream3dvATI");
	glad_glClientActiveVertexStreamATI = (PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC)load("glClientActiveVertexStreamATI");
	glad_glVertexBlendEnviATI = (PFNGLVERTEXBLENDENVIATIPROC)load("glVertexBlendEnviATI");
	glad_glVertexBlendEnvfATI = (PFNGLVERTEXBLENDENVFATIPROC)load("glVertexBlendEnvfATI");
}